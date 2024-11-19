//
// Created by admin on 10/10/2024.
//

#ifndef PIECE_H
#define PIECE_H

#include "data.h"

namespace Cattris {
    class Board;
    class CollisionMap;

    class Piece {
        public:
            i8 x = 0;
            i8 y = 0;
            PIECE piece = PIECE::NOTHING;
            ROTATION facing = ROTATION::NORTH;

        public:
            bool operator==(const Piece &other);

        public:
            Piece();

            Piece(i8 x, i8 y, PIECE p, ROTATION r);

        public:
            bool moveCW(CollisionMap& colmap);
            bool moveCCW(CollisionMap& colmap);
            bool moveLeft(CollisionMap& colmap);
            bool moveRight(CollisionMap& colmap);
            bool moveSD(CollisionMap& colmap);
    };
}

#endif
