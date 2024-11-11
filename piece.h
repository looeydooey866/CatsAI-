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
            int8_t x = 0;
            int8_t y = 0;
            PIECE piece = PIECE::NOTHING;
            ROTATION facing = ROTATION::NORTH;

        public:
            bool operator==(const Piece &other);

        public:
            Piece();

            Piece(int8_t x, int8_t y, PIECE p, ROTATION r);

        public:
            void draw(sf::RenderWindow &window);
            void drawShadow(sf::RenderWindow &window);

        public:
            bool moveCW(Board& board, CollisionMap& colmap);
            bool moveCCW(Board& board, CollisionMap& colmap);
            bool moveLeft(Board& board, CollisionMap& colmap);
            bool moveRight(Board& board, CollisionMap& colmap);
            bool moveSD(Board& board, CollisionMap& colmap);
            bool moveCW(Board& board);
            bool moveCCW(Board& board);
            bool moveLeft(Board& board);
            bool moveRight(Board& board);
            void moveSD(Board& board);
            void place(Board& board);
    };
}

#endif
