//
// Created by admin on 11/25/2024.
//

#ifndef COLMAP_H
#define COLMAP_H
#include "data.h"
#include "piece.h"
#include "board.h"

namespace Cattris {
    class Board;
    class Piece;

class CollisionMap {
        public:
            uint32_t map[4][10];

        public:
            void populate(Board& board, PieceType piece);

            bool colliding(int8_t x, int8_t y, Rotation rot, PieceType piece) const;

            bool colliding(Piece &p) const;

            uint8_t height(Rotation rot, int8_t x, int8_t y, PieceType piece);

            void getHeightArray(Rotation rot, uint8_t height[10], PieceType piece);

            void print(int rot);

            long long benchColmap(Board& board,PieceType piece, int runs);

            long long benchColmapAllPieces(Board& board, int runs);
    };


} // Cattris

#endif //COLMAP_H
