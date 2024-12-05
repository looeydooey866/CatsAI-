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
        uint32_t data[4][10] = {0};

    public:
        void set(Rotation r, int8_t x, int8_t y, PieceType p);
        bool get(Rotation r, int8_t x, int8_t y, PieceType p) const;
        bool get(Cattris::Move m) const;
        uint32_t column(Rotation r, int8_t x) const;

        void softdrop(CollisionMap &colmap);

        void softdrop(uint8_t x, Rotation r, CollisionMap &colmap);

        void spread(const CollisionMap &colmap);

        void rotate(const CollisionMap &colmap, const PieceType p);

        void removeDuplicates(PieceType p);
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

    std::vector<Move> Moves(Board& board, const Piece& piece);
    long long benchMovegen(Board &board, Piece &piece);
    void flip(uint32_t &mask);
}
#endif //MOVEGEN_H