#ifndef DATA_H
#define DATA_H

#include "include.h"

namespace Cattris {
    enum PIECE : uint8_t {
        S,
        Z,
        I,
        O,
        L,
        T,
        J,
        NOTHING
    };

    enum TSPIN : uint8_t {
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

    enum MOVE : uint8_t {
        LEFT,
        RIGHT,
        CW,
        CCW,
        DROP
    };

    enum ROTATION : uint8_t {
        NORTH,
        EAST,
        SOUTH,
        WEST
    };

#define pr(x,y) {(x),(y)}

    constexpr int8_t CW_KICK_DATA[2][4][5][2] = {
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

    constexpr int8_t CCW_KICK_DATA[2][4][5][2] = {
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
    constexpr uint8_t PIECE_COORDINATES[7][4][4][2] = {
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

    constexpr int8_t CENTER_OSETS[7][4][4][2] ={
        //i'm sorry (not sorry)
        //S Z I O L T J
        //Gives offset from leftmost bottommost piece
        {{{0,0}, {1,0}, {1,1}, {2,1}},
        {{0,0}, {0,1}, {1,-1}, {1,0}},
        {{0,0}, {1,0}, {1,1}, {2,1}},
        {{0,0}, {0,1}, {1,0}, {1,-1}}},
        {{{0,0}, {1,0}, {1,-1}, {2,-1}},
        {{0,0}, {0,1}, {1,1}, {1,2}},
        {{0,0}, {1,0}, {1,-1}, {2,-1}},
        {{0,0}, {0,1}, {1,1}, {1,2}}},
        {{{0,0}, {1,0}, {2,0}, {3,0}},
        {{0,0}, {0,1}, {0,2}, {0,3}},
        {{0,0}, {1,0}, {2,0}, {3,0}},
        {{0,0}, {0,1}, {0,2}, {0,3}}},
        {{{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}},
        {{0,0}, {0,1}, {1,0}, {1,1}}},
        {{{0,0}, {1,0}, {2,0}, {2,1}},
        {{0,0}, {0,1}, {0,2}, {1,0}},
        {{0,0}, {0,1}, {1,1}, {2,1}},
        {{0,0}, {1,-2}, {1,-1}, {1,0}}},
        {{{0,0}, {1,0}, {1,1}, {2,0}},
        {{0,0}, {0,1}, {0,2}, {1,1}},
        {{0,0}, {1,0}, {2,0}, {1,-1}},
        {{0,0}, {1,-1}, {1,0}, {1,1}}},
        {{{0,0}, {0,1}, {1,0}, {2,0}},
        {{0,0}, {0,1}, {0,2}, {1,2}},
        {{0,0}, {1,0}, {2,0}, {2,-1}},
        {{0,0}, {1,0}, {1,1}, {1,2}}}
    };
#undef quad
#undef pr

    constexpr uint8_t PIECE_SYMMETRY[7] = {2,2,2,1,4,4,4};
}
#endif //DATA_H
