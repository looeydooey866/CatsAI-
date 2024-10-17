#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#include "board.h"
#include "point.h"
#include "piece.h"

Piece::Piece(string p, Board &b, sf::RenderWindow &w): piece(std::move(p)), rotations(0), coords(0, 0), board(b), window(w) {
    updateBitset();
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

int Piece::getOset() {
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

bool Piece::isNotColliding() {
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
    return Point(-866,-866);
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
    return Point(-866,-866);
}

vector<vector<Point>> Piece::getCWKickData() {
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

vector<vector<Point>> Piece::getCCWKickData() {
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
            ans.push_back(Point(3-(i%4)+coords.x,i/4 + coords.y));
        }
    }
    return ans;
}

void Piece::placePiece() {
    if (!isNotColliding()) __gnu_cxx::__throw_concurrence_broadcast_error();
    vector<Point> coords = getCoords();
    for (auto coord : coords) {
        board.coloredBoard[coord.y][coord.x] = piece;
        board.bitBoard[9 - coord.x + 10 * coord.y] = 1;
    }
}

void Piece::draw() {
    //the left is 15, the right is 135
    vector<Point> v = getCoords();
    for (auto pr : v) {
        sf::RectangleShape block(sf::Vector2f(30,30));
        block.setPosition(150 + pr.x * 30, 150 + (20 - pr.y) * 30);
        block.setFillColor(clrIdentify(piece));
        window.draw(block);
    }
}

int Piece::getLeftSpace() {
    int ans = 0;
    bitset<16> LEFTMASK = bitset<16>("1000100010001000");
    while ((LEFTMASK & boundingBox).none()) {
        LEFTMASK >>= 1;
        ans++;
    }
    return ans;
}

int Piece::getRightSpace() {
    int ans = 0;
    bitset<16> RIGHTMASK = bitset<16>("000100010001");
    while ((RIGHTMASK & boundingBox).none()) {
        RIGHTMASK <<= 1;
        ans++;
    }
    return ans;
}

void Piece::stringToMove(string s) {
    if (s=="dasleft") {
        dasleft();
    }
    else if (s=="dasright") {
        dasright();
    }
    else if (s=="left") {
        left();
    }
    else if (s=="right") {
        right();
    }
    else if (s=="sd") {
        sd();
    }
    else if (s=="cw") {
        cw();
    }
    else if (s=="ccw") {
        ccw();
    }
}

inline long long hahs(Point point, int rotations) {
    return (long long)point.x + (long long)point.y << 4 + (long long) rotations << 6;
}

/*vector<pair<vector<string>, Piece>> Piece::getEndPositions() {
    __gnu_pbds::gp_hash_table<long long, bool> visited;
    Piece copyOfPiece = *this;
    copyOfPiece.spawn();
    vector<pair<vector<string>, Piece>> endPos;
    unordered_map<long long, vector<string>> paths;

    // Comparator to use in the priority queue
    auto cmp = [&paths](const Piece& a, const Piece& b) {
        long long hashA = hahs(a.coords, a.rotations);
        long long hashB = hahs(b.coords, b.rotations);
        return paths[hashA].size() > paths[hashB].size(); // Min-heap based on path lengths
    };

    // Initialize the priority queue with the custom comparator
    priority_queue<Piece, vector<Piece>, decltype(cmp)> pq(cmp);

    pq.push(Piece(copyOfPiece.piece,copyOfPiece.board,copyOfPiece.window));
    paths[hahs(copyOfPiece.coords, copyOfPiece.rotations)] = {""};

    while (!pq.empty()) {
        Piece curpiece = pq.top();
        pq.pop();

        long long currentHash = hahs(curpiece.coords, curpiece.rotations);
        if (visited[currentHash]) {
            continue; // Skip if already visited
        }
        visited[currentHash] = true;

        // Check if the current piece cannot move down, indicating it's an end position
        if (!curpiece.canMoveDown()) {
            endPos.emplace_back(paths[currentHash], curpiece); // Store path and piece
        }

        // Loop through possible moves
        for (const auto& move : moves) {
            vector<string> moveHistory = paths[currentHash];
            // Avoid reversing the last move
            if ((move == "l" && !moveHistory.empty() && moveHistory.back() == "r") ||
                (move == "r" && !moveHistory.empty() && moveHistory.back() == "l") ||
                (move == "sd" && !moveHistory.empty() && moveHistory.back() == "sd") ||
                (move == "dasleft" && !moveHistory.empty() && moveHistory.back() == "dasleft") ||
                (move == "dasright" && !moveHistory.empty() && moveHistory.back() == "dasright")) {
                continue; // Skip invalid moves
            }

            Piece newpiece = curpiece;
            newpiece.stringToMove(move); // Apply the move
            moveHistory.push_back(move);

            long long newHash = hahs(newpiece.coords, newpiece.rotations);
            // Update paths if the new path is shorter
            if (paths.find(newHash) == paths.end() || moveHistory.size() < paths[newHash].size()) {
                paths[newHash] = moveHistory;
                pq.push(newpiece); // Add new piece state to the queue
            }
        }
    }
    return endPos; // Return collected end positions
}*/



