//
// Created by admin on 10/10/2024.
//

#ifndef PIECE_H
#define PIECE_H
#include "board.h"
#include "point.h"

inline vector<string> moves = {"dasleft","dasright","left","right","cw","ccw","sd"};



struct Piece {
    string piece;
    int rotations;
    Point coords;
    bitset<16> boundingBox;
    Board& board;
    sf::RenderWindow& window;
    Piece(string p, Board& b, sf::RenderWindow& w);



    bitset<16> getBitset();

    void updateBitset();

    int getOset();

    void spawn();

    [[nodiscard]] bool isNotColliding();

    bool canMoveLeft();

    bool canMoveRight();

    void left();

    void right();

    void dasleft();

    void dasright();

    bool canMoveDown();

    void sd();

    void cw();

    void ccw();

    Point cwKickCheck();

    Point ccwKickCheck();

    vector<vector<Point>> getCWKickData();

    vector<vector<Point>> getCCWKickData();

    const array<bitset<16>,4> TBITSET = {bitset<16>(1248),bitset<16>(1124),bitset<16>(228),bitset<16>(1220)};
    const array<bitset<16>,4> SBITSET = {bitset<16>(1728),bitset<16>(1122),bitset<16>(108),bitset<16>(2244)};
    const array<bitset<16>,4> ZBITSET = {bitset<16>(3168),bitset<16>(612),bitset<16>(198),bitset<16>(1224)};
    const array<bitset<16>,4> IBITSET = {bitset<16>(3840),bitset<16>(8738),bitset<16>(240),bitset<16>(17476)};
    const array<bitset<16>,4> OBITSET = {bitset<16>(1632),bitset<16>(1632),bitset<16>(1632),bitset<16>(1632)};
    const array<bitset<16>,4> LBITSET = {bitset<16>(736),bitset<16>(1094),bitset<16>(232),bitset<16>(3140)};
    const array<bitset<16>,4> JBITSET = {bitset<16>(2272),bitset<16>(1604),bitset<16>(226),bitset<16>(1100)};

    vector<Point> getCoords();

    void placePiece();

    void draw();

    int getLeftSpace();

    int getRightSpace();

    void stringToMove(string s);

    vector<pair<vector<string>,Piece>> getEndPositions();
};



inline long long hahs(Point point, int rotations);

#endif //PIECE_H
