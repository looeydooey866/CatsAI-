#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>

#include "myheap.h"
using namespace std;
#include "board.h"
#include "point.h"
#include "piece.h"

Piece::Piece(std::string p, Board& b, sf::RenderWindow& w)
    : piece(p), board(b), window(w), rotations(0), coords(Point(0,0)) {
    updateBitset();
    spawn();
}

bitset<16> Piece::getBitset() {
    if (piece == "T") return TBITSET[rotations];
    if (piece == "S") return SBITSET[rotations];
    if (piece == "Z") return ZBITSET[rotations];
    if (piece == "J") return JBITSET[rotations];
    if (piece == "L") return LBITSET[rotations];
    if (piece == "O") return OBITSET[0];
    if (piece == "I") return IBITSET[rotations];
    return -1;
}

void Piece::updateBitset() {
    boundingBox = getBitset();
}

int Piece::getOset() const {
    if (piece == "O") {
        return 4;
    }
    else {
        return 3;
    }
}

void Piece::spawn() {
    rotations = 0;
    coords = Point(getOset()-getLeftSpace(),17);
    boundingBox = getBitset();
}

bool Piece::isNotColliding() const {
    bitset<40> blockblock;

    for (int i=0;i<4;i++) {
        if(coords.y + i < 0) {
            if (((boundingBox >> i * 4) & bitset<16>("1111")).any()) {
                return false;
            }
            continue;
        }

        bitset<40> row = (bitset<40>((boundingBox.to_ulong()) >> (i * 4)) & bitset<40>(15)) << 6;
        if (coords.x >= 0) row >>= coords.x;
        else row <<= -coords.x;
        if ((row & bitset<40>("1111111111111111111111111111110000000000")).any()) {
            return false;
        }
        blockblock |= (row << i * 10);
    }
    bitset<40> boardChunk;
    if (coords.y >= 0) boardChunk = bitset<40>((board.bitBoard>> coords.y * 10).to_string().substr(210));
    else boardChunk = bitset<40>((board.bitBoard << (abs(coords.y) * 10)).to_string().substr(210));

    if (blockblock.count() != 4) {
        return false;
    }

    return (boardChunk & blockblock).none();
}

bool Piece::canMoveLeft() {
    Piece newpiece = *this;
    newpiece.coords.x--;
    return (newpiece.isNotColliding());
}

bool Piece::canMoveRight() {
    Piece newpiece = *this;
    newpiece.coords.x++;
    return (newpiece.isNotColliding());
}

void Piece::left() {
    if (canMoveLeft()) {
        coords.x--;
    }
}

void Piece::right() {
    if (canMoveRight()) {
        coords.x++;
    }
}

void Piece::dasleft() {
    while (canMoveLeft()) {
        left();
    }
}

void Piece::dasright() {
    while (canMoveRight()) {
        right();
    }
}

bool Piece::canMoveDown() {
    Piece newpiece = *this;
    newpiece.coords.y--;
    return (newpiece.isNotColliding());
}

void Piece::sd() {
    while (canMoveDown()) {
        coords.y--;
    }
}

void Piece::cw() {
    Point x = cwKickCheck();
    if (x.x != -866) {
        rotations++;
        rotations %= 4;
        coords.x += x.x;
        coords.y += x.y;
        updateBitset();
    }
}

void Piece::ccw() {
    Point x = ccwKickCheck();
    if (x.x != -866) {
        rotations--;
        rotations += 8;
        rotations %= 4;
        coords.x += x.x;
        coords.y += x.y;
        updateBitset();
    }
}

Point Piece::cwKickCheck() {
    vector<Point> kicks = getCWKickData()[rotations];
    for (auto kick : kicks) {
        Piece newpiece = *this;
        newpiece.coords.x += kick.x;
        newpiece.coords.y += kick.y;
        newpiece.rotations++;
        newpiece.rotations %= 4;
        newpiece.updateBitset();
        if (newpiece.isNotColliding()) {
            return kick;
        }
    }
    return {-866,-866};
}

Point Piece::ccwKickCheck() {
    const vector<Point> kicks = getCCWKickData()[piece=="O"?0:rotations];
    for (auto kick : kicks) {
        Piece newpiece = *this;
        newpiece.coords.x += kick.x;
        newpiece.coords.y += kick.y;
        newpiece.rotations--;
        newpiece.rotations += 8;
        newpiece.rotations %= 4;
        newpiece.updateBitset();
        if (newpiece.isNotColliding()) {
            return kick;
        }
    }
    return {-866,-866};
}

vector<vector<Point>> Piece::getCWKickData() const {
    if (set<string>{"S","Z","J","L","T"}.contains(piece)) {
        return {
            {
                Point(0,0),
                Point(-1,0),
                Point(-1,1),
                Point(0,-2),
                Point(-1,-2)
            },
            {
                Point(0,0),
                Point(1,0),
                Point(1,-1),
                Point(0,2),
                Point(1,2)
            },
            {
                Point(0,0),
                Point(1,0),
                Point(1,1),
                Point(0,-2),
                Point(1,-2)
            },
            {
                Point(0,0),
                Point(-1,0),
                Point(-1,-1),
                Point(0,2),
                Point(-1,2)
            }
        };
    }
    else if (piece == "O") {
        return {{Point(0,0)}};
    }
    else {
        return {
            {
                Point(0,0),
                Point(-2,0),
                Point(1,0),
                Point(-2,-1),
                Point(1,2)
            },
            {
                Point(0,0),
                Point(-1,0),
                Point(2,0),
                Point(-1,2),
                Point(2,-1)
            },
            {
                Point(0,0),
                Point(2,0),
                Point(-1,0),
                Point(2,1),
                Point(-1,-2)
            },
            {
                Point(0,0),
                Point(1,0),
                Point(-2,0),
                Point(1,-2),
                Point(-2,1)
            }
        };
    }
}

vector<vector<Point>> Piece::getCCWKickData() const {
    if (set<string>{"S","Z","J","L","T"}.contains(piece)) {
        return {
                {
                    Point(0,0),
                    Point(1,0),
                    Point(1,1),
                    Point(0,-2),
                    Point(1,-2)
                 },
                 {
                     Point(0,0),
                     Point(1,0),
                     Point(1,-1),
                     Point(0,2),
                     Point(1,2)
                  },
                  {
                      Point(0,0),
                      Point(-1,0),
                      Point(-1,1),
                      Point(0,-2),
                      Point(-1,-2)
                   },
                   {
                       Point(0,0),
                       Point(-1,0),
                       Point(-1,-1),
                       Point(0,2),
                       Point(-1,2)
                    }


        };
    }
    else if (piece == "O") {
        return {{Point(0,0)}};
    }
    else {
        return {
                {
                    Point(0,0),
                    Point(-1,0),
                    Point(2,0),
                    Point(-1,2),
                    Point(2,-1)
                },
            {
                Point(0,0),
                Point(2,0),
                Point(-1,0),
                Point(2,1),
                Point(-1,-2)
            },
            {
                Point(0,0),
                Point(1,0),
                Point(-2,0),
                Point(1,-2),
                Point(-2,1)
            },
            {
                Point(0,0),
                Point(-2,0),
                Point(1,0),
                Point(-2,-1),
                Point(1,2)
            }

        };
    }
}

vector<Point> Piece::getCoords() {
    vector<Point> ans;
    for (int i=0;i<16;i++) {
        if (boundingBox[i]) {
            ans.emplace_back(3-(i%4)+coords.x,i/4 + coords.y);
        }
    }
    return ans;
}

void Piece::placePiece() {
    if (!isNotColliding()) {
        cerr << "Yo, line 336 of piece.cpp! HEEEEEELLLLLLLLLPPPPPPPP";
        vector<int> bruhh(1LL<<9999999999);
    }
    for (vector<Point> coords = getCoords(); auto coord : coords) {
        board.coloredBoard[coord.y][coord.x] = piece;
        board.bitBoard[9 - coord.x + 10 * coord.y] = true;
    }
}

void Piece::draw() {
    //the left is 15, the right is 135
    vector<Point> v = getCoords();
    for (auto pr : v) {
        sf::RectangleShape block(sf::Vector2f(30,30));
        block.setPosition(pr.x * 30 + 150, (20 - pr.y) * 30 + 150);
        block.setFillColor(clrIdentify(piece));
        window.draw(block);
    }
}

int Piece::getLeftSpace() const {
    int ans = 0;
    auto LEFTMASK = bitset<16>("1000100010001000");
    while ((LEFTMASK & boundingBox).none()) {
        LEFTMASK >>= 1;
        ans++;
    }
    return ans;
}

int Piece::getRightSpace() const {
    int ans = 0;
    auto RIGHTMASK = bitset<16>("000100010001");
    while ((RIGHTMASK & boundingBox).none()) {
        RIGHTMASK <<= 1;
        ans++;
    }
    return ans;
}

void Piece::stringToMove(const string& currentMoveBeingProcessed) {
    if (currentMoveBeingProcessed=="dasleft") {
        dasleft();
    }
    else if (currentMoveBeingProcessed=="dasright") {
        dasright();
    }
    else if (currentMoveBeingProcessed=="left") {
        left();
    }
    else if (currentMoveBeingProcessed=="right") {
        right();
    }
    else if (currentMoveBeingProcessed=="sd") {
        sd();
    }
    else if (currentMoveBeingProcessed=="cw") {
        cw();
    }
    else if (currentMoveBeingProcessed=="ccw") {
        ccw();
    }
}

inline long long posHash(Point point, int rotations) {
    return (long long)point.x + (long long)point.y << 4 + (long long) rotations << 6;
}

vector<pair<vector<string>, Piece>> Piece::getEndPositions() {
    //
    // WORK IN PROGRESS
    //
    __gnu_pbds::gp_hash_table<long long, bool> visited;
    Piece copyOfPiece = *this;
    copyOfPiece.spawn();
    vector<pair<vector<string>, Piece>> endPos;
    unordered_map<long long, vector<string>> paths;
    MyHeap pq;

    pq.insert(copyOfPiece,0);
    paths[posHash(copyOfPiece.coords, copyOfPiece.rotations)] = {""};

    while (!pq.pieces.empty()) {
        Piece curpiece = pq.top();
        pq.pop();

        long long currentHash = posHash(curpiece.coords, curpiece.rotations);
        if (visited[currentHash]) {
            continue;
        }
        visited[currentHash] = true;

        if (!curpiece.canMoveDown()) {
            endPos.emplace_back(paths[currentHash], curpiece);
        }

        for (const auto& move : moves) {
            vector<string> moveHistory = paths[currentHash];
            if ((move == "l" && !moveHistory.empty() && moveHistory.back() == "r") ||
                (move == "r" && !moveHistory.empty() && moveHistory.back() == "l") ||
                (move == "sd" && !moveHistory.empty() && moveHistory.back() == "sd") ||
                (move == "dasleft" && !moveHistory.empty() && moveHistory.back() == "dasleft") ||
                (move == "dasright" && !moveHistory.empty() && moveHistory.back() == "dasright")) {
                continue;
            }

            Piece newpiece = curpiece;
            newpiece.stringToMove(move);
            moveHistory.push_back(move);

            long long newHash = posHash(newpiece.coords, newpiece.rotations);

            if (paths.find(newHash) == paths.end() || moveHistory.size() < paths[newHash].size()) {
                paths[newHash] = moveHistory;
                pq.insert(newpiece,5);
            }
        }
    }
    return endPos;
}



