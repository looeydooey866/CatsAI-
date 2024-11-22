// Board.h
#ifndef BOARD_H
#define BOARD_H
#include "data.h"

using namespace std;

namespace Cattris {
    class Piece;
    class CollisionMap;
    class MoveGenMap;

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

            ui8 height(ui8 x);

            void getHeightArray(ui8 height[10]);

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

            bool colliding(i8 x, i8 y, ROTATION rot, PIECE piece) const;

            bool colliding(Piece &p) const;

            ui8 height(ROTATION rot, ui8 x, PIECE piece);

            void getHeightArray(ROTATION rot, ui8 height[10], PIECE piece);

            void print(int rot);

            long long benchColmap(Board board,PIECE piece, int runs);

            long long benchColmapAllPieces(Board board, int runs);

            void loadToMovegen(MoveGenMap &mgen);
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
