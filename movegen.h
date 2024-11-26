#ifndef MOVEGEN_H
#define MOVEGEN_H
#include "data.h"
#include "piece.h"

namespace Cattris {
    class Board;
    class CollisionMap;
    class Piece;
    class Move;

    class MovegenMap {
        public:
        bool data[4][10][25] = {false};

        public:
        void set(Rotation r, int8_t x, int8_t y, PieceType p);
        bool get(Rotation r, int8_t x, int8_t y, PieceType p);
        bool get(Cattris::Move m);
    };

    class Move {
        public:
        int8_t x = 0;
        int8_t y = 0;
        Rotation facing = Rotation::North;
        PieceType type;

        public:
        Move(Rotation r, int8_t x, int8_t y, PieceType p);

        public:
        void normalize();
        bool moveCCW(CollisionMap& colmap);
        bool moveCW(CollisionMap& colmap);
    };

    std::vector<Move> Moves(Board& board, Piece& piece);
    long long benchMovegen(Board &board, Piece &piece);
}
#endif //MOVEGEN_H
