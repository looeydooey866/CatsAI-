#ifndef DATA_H
#define DATA_H

#include "include.h"
#include <SFML/Graphics.hpp>
#include <immintrin.h>
typedef int_fast8_t i8;
typedef int_fast16_t i16;
typedef int_fast32_t i32;
typedef int_fast64_t i64;
typedef uint_fast8_t ui8;
typedef uint_fast16_t ui16;
typedef uint_fast32_t ui32;
typedef uint_fast64_t ui64;

namespace Cattris {
    enum PIECE : ui8 {
        S,
        Z,
        I,
        O,
        L,
        T,
        J,
        NOTHING
    };

    enum TSPIN : ui8 {
        UNKNOWN,
        MINI,
        NORMAL
    };

    static std::string piece_to_string(PIECE piece) {
        switch (piece) {
            case PIECE::S: return "S";
            case PIECE::Z: return "Z";
            case PIECE::I: return "I";
            case PIECE::O: return "O";
            case PIECE::L: return "L";
            case PIECE::T: return "T";
            case PIECE::J: return "J";
        }
    }

    static char piece_to_char(PIECE piece) {
        switch(piece) {
            case PIECE::S: return 'S';
            case PIECE::Z: return 'Z';
            case PIECE::I: return 'I';
            case PIECE::O: return 'O';
            case PIECE::L: return 'L';
            case PIECE::T: return 'T';
            case PIECE::J: return 'J';
        }
    }

    enum MOVE : ui8 {
        LEFT,
        RIGHT,
        CW,
        CCW,
        DROP
    };

    enum ROTATION : ui8 {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

#define pr(x,y) {(x),(y)}

    constexpr i8 CW_KICK_DATA[2][4][5][2] = {
        //     fanum 11/11/2024 4:16 PM
        {
            {pr(0, 0),pr(-1, 0),pr(-1, 1),pr(0, -2),pr(-1, -2)},
            {pr(0, 0),pr(1, 0),pr(1, -1),pr(0, 2),pr(1, 2)},
            {pr(0, 0),pr(1, 0),pr(1, 1),pr(0, -2),pr(1, -2)},
            {pr(0, 0),pr(-1, 0),pr(-1, -1),pr(0, 2),pr(-1, 2)}
        },
        {
                    {pr(0, 0),pr(-2, 0),pr(1, 0),pr(-2, -1),pr(1, 2)},
                    {pr(0, 0),pr(-1, 0),pr(2, 0),pr(-1, 2),pr(2, -1)},
                    {pr(0, 0),pr(2, 0),pr(-1, 0),pr(2, 1),pr(-1, -2)},
                    {pr(0, 0),pr(1, 0),pr(-2, 0),pr(1, -2),pr(-2, 1)}
        }
    };

    constexpr i8 CCW_KICK_DATA[2][4][5][2] = {
        {
            {pr(0, 0),pr(1, 0),pr(1, 1),pr(0, -2),pr(1, -2)},
            {pr(0, 0),pr(1, 0),pr(1, -1),pr(0, 2),pr(1, 2)},
            {pr(0, 0),pr(-1, 0),pr(-1, 1),pr(0, -2),pr(-1, -2)},
            {pr(0, 0),pr(-1, 0),pr(-1, -1),pr(0, 2),pr(-1, 2)}
        },
        {
                    {pr(0, 0),pr(-1, 0),pr(2, 0),pr(-1, 2),pr(2, -1)},
                    {pr(0, 0),pr(2, 0),pr(-1, 0),pr(2, 1),pr(-1, -2)},
                    {pr(0, 0),pr(1, 0),pr(-2, 0),pr(1, -2),pr(-2, 1)},
                    {pr(0, 0),pr(-2, 0),pr(1, 0),pr(-2, -1),pr(1, 2)}
        }
    };

#define quad(a,b,c,d,e,f,g,h) {pr((a),(b)),pr((c),(d)),pr((e),(f)),pr((g),(h))}

    constexpr i8 PIECE_COORDINATES[7][4][4][2] = {
        //first coordinate is the leftmost, and bottommost point
        //S Z I O L T J
        {quad(0, 1, 1, 1, 1, 2, 2, 2),quad(1, 1, 1, 2, 2, 0, 2, 1),quad(0, 0, 1, 0, 1, 1, 2, 1),quad(0, 1, 0, 2, 1, 1, 1, 0)},
        {quad(0, 2, 1, 2, 1, 1, 2, 1),quad(1, 0, 1, 1, 2, 1, 2, 2),quad(0, 1, 1, 1, 1, 0, 2, 0),quad(0, 0, 0, 1, 1, 1, 1, 2) },
        {quad(0, 2, 1, 2, 2, 2, 3, 2),quad(2, 0, 2, 1, 2, 2, 2, 3),quad(0, 1, 1, 1, 2, 1, 3, 1),quad(1, 0, 1, 1, 1, 2, 1, 3) },
        {quad(1, 1, 1, 2, 2, 1, 2, 2),quad(1, 1, 1, 2, 2, 1, 2, 2),quad(1, 1, 1, 2, 2, 1, 2, 2),quad(1, 1, 1, 2, 2, 1, 2, 2) },
        {quad(0, 1, 1, 1, 2, 1, 2, 2),quad(1, 0, 1, 1, 1, 2, 2, 0),quad(0, 0, 0, 1, 1, 1, 2, 1),quad(0, 2, 1, 0, 1, 1, 1, 2) },
        {quad(0, 1, 1, 1, 1, 2, 2, 1),quad(1, 0, 1, 1, 1, 2, 2, 1),quad(0, 1, 1, 1, 2, 1, 1, 0),quad(0, 1, 1, 0, 1, 1, 1, 2) },
        {quad(0, 1, 0, 2, 1, 1, 2, 1),quad(1, 0, 1, 1, 1, 2, 2, 2),quad(0, 1, 1, 1, 2, 1, 2, 0),quad(0, 0, 1, 0, 1, 1, 1, 2)  }
    };

    constexpr i8 CENTER_OSETS[7][4][4][2] = {
        //i'm sorry (not sorry)
        //S Z I O L T J
        //Gives offset from leftmost bottommost piece
        {
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{0, 0}, {0, 1}, {1, -1}, {1, 0}},
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{0, 0}, {0, 1}, {1, 0}, {1, -1}}
        },
        {
                {{0, 0}, {1, 0}, {1, -1}, {2, -1}},
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
                {{0, 0}, {1, 0}, {1, -1}, {2, -1}},
                {{0, 0}, {0, 1}, {1, 1}, {1, 2}}
        },
        {
                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
                {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {0, 3}}
        },
        {
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
                {{0, 0}, {0, 1}, {1, 0}, {1, 1}}
        },
        {
                {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
                {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
                {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
                {{0, 0}, {1, -2}, {1, -1}, {1, 0}}
        },
        {
                {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
                {{0, 0}, {1, 0}, {2, 0}, {1, -1}},
                {{0, 0}, {1, -1}, {1, 0}, {1, 1}}
        },
        {
                {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
                {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                {{0, 0}, {1, 0}, {2, 0}, {2, -1}},
                {{0, 0}, {1, 0}, {1, 1}, {1, 2}}
        }
    };

    constexpr i8 DELTA_FROM_LAST_MINO[7][4][3][2] = {
        //this is basically a sin but whatever :3
        {{{1, 0}, {0, 1}, {1, 0}}, {{0, 1}, {1, -2}, {0, 1}}, {{1, 0}, {0, 1}, {1, 0}}, {{0, 1}, {1, -1}, {0, -1}},},
        {{{1, 0}, {0, -1}, {1, 0}}, {{0, 1}, {1, 0}, {0, 1}}, {{1, 0}, {0, -1}, {1, 0}}, {{0, 1}, {1, 0}, {0, 1}},},
        {{{1, 0}, {1, 0}, {1, 0}}, {{0, 1}, {0, 1}, {0, 1}}, {{1, 0}, {1, 0}, {1, 0}}, {{0, 1}, {0, 1}, {0, 1}},},
        {{{0, 1}, {1, -1}, {0, 1}}, {{0, 1}, {1, -1}, {0, 1}}, {{0, 1}, {1, -1}, {0, 1}}, {{0, 1}, {1, -1}, {0, 1}},},
        {{{1, 0}, {1, 0}, {0, 1}}, {{0, 1}, {0, 1}, {1, -2}}, {{0, 1}, {1, 0}, {1, 0}}, {{1, -2}, {0, 1}, {0, 1}},},
        {{{1, 0}, {0, 1}, {1, -1}}, {{0, 1}, {0, 1}, {1, -1}}, {{1, 0}, {1, 0}, {-1, -1}}, {{1, -1}, {0, 1}, {0, 1}},},
        {{{0, 1}, {1, -1}, {1, 0}}, {{0, 1}, {0, 1}, {1, 0}}, {{1, 0}, {1, 0}, {0, -1}}, {{1, 0}, {0, 1}, {0, 1}},}
    };;;
    constexpr bool DELTA_Y_IS_POSITIVE[7][4][3] = {
        {{true, true, true}, {true, false, true}, {true, true, true}, {true, false, false}},
        {{true, false, true}, {true, true, true}, {true, false, true}, {true, true, true}},
        {{true, true, true}, {true, true, true}, {true, true, true}, {true, true, true}},
        {{true, false, true}, {true, false, true}, {true, false, true}, {true, false, true}},
        {{true, true, true}, {true, true, false}, {true, true, true}, {false, true, true}},
        {{true, true, false}, {true, true, false}, {true, true, false}, {false, true, true}},
        {{true, false, true}, {true, true, true}, {true, true, false}, {true, true, true}}
    };
#undef quad
#undef pr

    constexpr ui8 PIECE_SYMMETRY[7] = {2,2,2,1,4,4,4};
}
#endif //DATA_H
