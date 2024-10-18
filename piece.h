//
// Created by admin on 10/10/2024.
//

#ifndef PIECE_H
#define PIECE_H

#include <bits/stdc++.h>
struct Board;
#include "point.h"
#include <SFML/Graphics.hpp>

inline std::vector<std::string> moves = {"cw","ccw","dasleft","dasright","left","right","sd"};

struct Piece {
    std::string piece;
    int rotations;
    Point coords;
    std::bitset<16> boundingBox;
    Board& board;
    sf::RenderWindow& window;
    std::string lastKick = "";

    Piece(std::string p, Board& b, sf::RenderWindow& w);

    std::bitset<16> getBitset();
    void updateBitset();
    int getOset() const;
    void spawn();
    [[nodiscard]] bool isNotColliding() const;
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
    std::vector<std::vector<Point>> getCWKickData() const;
    std::vector<std::vector<Point>> getCCWKickData() const;

    //turned these into integers to ease on the eyes
    const std::array<std::bitset<16>, 4> TBITSET = {std::bitset<16>(1248), std::bitset<16>(1124), std::bitset<16>(228), std::bitset<16>(1220)};
    const std::array<std::bitset<16>, 4> SBITSET = {std::bitset<16>(1728), std::bitset<16>(1122), std::bitset<16>(108), std::bitset<16>(2244)};
    const std::array<std::bitset<16>, 4> ZBITSET = {std::bitset<16>(3168), std::bitset<16>(612), std::bitset<16>(198), std::bitset<16>(1224)};
    const std::array<std::bitset<16>, 4> IBITSET = {std::bitset<16>(3840), std::bitset<16>(8738), std::bitset<16>(240), std::bitset<16>(17476)};
    const std::array<std::bitset<16>, 4> OBITSET = {std::bitset<16>(1632), std::bitset<16>(1632), std::bitset<16>(1632), std::bitset<16>(1632)};
    const std::array<std::bitset<16>, 4> LBITSET = {std::bitset<16>(736), std::bitset<16>(1094), std::bitset<16>(232), std::bitset<16>(3140)};
    const std::array<std::bitset<16>, 4> JBITSET = {std::bitset<16>(2272), std::bitset<16>(1604), std::bitset<16>(226), std::bitset<16>(1100)};

    std::vector<Point> getCoords();
    void placePiece();
    void draw();
    int getLeftSpace() const;
    int getRightSpace() const;
    void stringToMove(const std::string& currentMoveBeingProcessed);
    std::vector<std::pair<std::vector<std::string>, Piece>> getEndPositions();

    std::string tSpinCheck() const;
    int getCollisions() const ;
};

inline void swapPiece(Piece& first, Piece& second) {
    std::swap(first.piece, second.piece);
    std::swap(first.boundingBox, second.boundingBox);
    std::swap(first.coords.x,second.coords.x);
    std::swap(first.coords.y,second.coords.y);
    std::swap(first.rotations, second.rotations);
}

inline std::bitset<250> posHash(Point point, int rotations);

#endif
