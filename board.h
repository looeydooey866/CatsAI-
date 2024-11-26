// Board.h
#ifndef BOARD_H
#define BOARD_H
#include "data.h"
#include "piece.h"

using namespace std;

namespace Cattris {
    class Piece;
    class CollisionMap;

    class Board {
        public:
            uint32_t board[10] = {false};

        public:
            uint32_t& operator [] (int index);
            bool operator == (const Board& other);

        public:
            void set(const int8_t& x, const int8_t& y);

            void setfill(const int8_t& x1, const int8_t& y1, const int8_t& x2, const int8_t& y2);

            void setstring(const string s, int y);

            void setBigString(const string s, int y);

            void place(Piece& p);

            void place(int8_t &x, int8_t &y, PieceType piece, Rotation rot);

            bool get(const int8_t& x, const int8_t& y);

            uint8_t height(uint8_t x);

            void getHeightArray(uint8_t height[10]);

            Tspin isTspin(Piece &p);

            Tspin isTspin(const int8_t px, const int8_t py, Rotation rotation, PieceType piece);

            uint32_t getMask();

            uint8_t fullLines();

            void clearLines();

            void print();
    };


}
#endif
