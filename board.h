// Board.h
#ifndef BOARD_H
#define BOARD_H
#include "data.h"

using namespace std;

namespace Cattris {
    class Piece;
    class CollisionMap;

    class Board {
        public:
            ui32 board[10] = {false};

        public:
            ui32& operator [] (int index);
            bool operator == (const Board& other);

        public:
            void set(const i8& x, const i8& y);

            void setfill(const i8& x1, const i8& y1, const i8& x2, const i8& y2);

            void setstring(const string s, int y);

            void setBigString(const string s, int y);

            void place(Piece& p);

            void place(i8 &x, i8 &y, PIECE piece, ROTATION rot);

            bool get(const i8& x, const i8& y);

            void getHeightArray(ui8 height[10]);

            bool isSet(const i8& x, i8& y);

            TSPIN isTspin(Piece &p);

            TSPIN isTspin(i8 x, i8 y, ROTATION rotation, PIECE piece);

            ui32 getMask();

            ui8 fullLines();

            void clearLines();

            void print();
    };

    class CollisionMap {
        public:
            ui32 map[4][10];

        public:
            void populate(Board& board, PIECE piece);

            bool colliding(const i8& x, const i8& y, ROTATION rot, PIECE piece);

            bool colliding(Piece &p);

            ui8 height(ROTATION rot, const ui8& x);

            void getHeightArray(ROTATION rot, ui8 height[10]);

            void print(int rot);

            long long benchColmap(Board board,PIECE piece, int runs);

            long long benchColmapAllPieces(Board board, int runs);
    };

    class PosMap {
        public:
            bool map[4][10][25];

        public:
            PosMap();

        public:
            void clear();
            void set(const i8 x, const i8 y, ROTATION r);
            bool get(const i8 x, const i8 y, ROTATION r);
    };

    class GameBoard {
        public:
            string coloredBoard[25] = {".........."};

        public:
            void clearLines();

            void set(int x, int y, char type);

            void clear();
    };
}
#endif
