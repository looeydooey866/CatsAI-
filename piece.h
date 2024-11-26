//
// Created by admin on 10/10/2024.
//

#ifndef PieceType_H
#define PieceType_H

#include "data.h"

namespace Cattris {
    enum PieceType {I, S, Z, O, L, T, J, Nothing};

    enum Rotation {North, East, South, West};

    enum Tspin {UNKNOWN, MINI, NORMAL};

    class Board;
    class CollisionMap;

    class Piece {
        public:
            int8_t x = 3;
            int8_t y = 20;
            PieceType piece = PieceType::Nothing;
            Rotation facing = Rotation::North;

        public:
            bool operator==(const Piece &other);

        public:
            Piece();

            Piece(int8_t x, int8_t y, PieceType p, Rotation r);

        public:
            uint8_t centerX();
            uint8_t centerY();
            bool moveCW(CollisionMap& colmap);
            bool moveCCW(CollisionMap& colmap);
            bool moveLeft(CollisionMap& colmap);
            bool moveRight(CollisionMap& colmap);
            bool moveSD(CollisionMap& colmap);
            void normalize();
    };
}

#endif
