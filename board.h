// Board.h
#ifndef BOARD_H
#define BOARD_H
#include "data.h"

using namespace std;

sf::Color clrIdentify(string s);

namespace Cattris {
    class Piece;

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

            bool get(const int8_t& x, const int8_t& y);

            void getHeightArray(uint8_t height[10]);

            bool isSet(const int8_t& x, int8_t& y);

            bool isTspin(Piece &p);

            uint32_t getMask();

            uint8_t fullLines();

            void clearLines();

            void print();
    };

    class CollisionMap {
        public:
            uint32_t map[4][10];

        public:
            void populate(Board& board, PIECE piece);

            bool colliding(const uint8_t& x, const uint8_t& y, ROTATION rot, PIECE piece);

            bool colliding(Piece &p);

            uint8_t height(ROTATION rot, const uint8_t& x);

            void getHeightArray(ROTATION rot, uint8_t height[10]);

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
            void set(const int8_t x, const int8_t y, ROTATION r, bool value);
            bool get(const int8_t x, const int8_t y, ROTATION r);
    };

    class GameBoard {
        public:
            string coloredBoard[10][25] = {"#"};

        public:
            void draw(sf::RenderWindow &window);

            void clearLines();

            void set(int x, int y, string type);

            void clear();
    };
}
#endif
