//
// Created by Maximus Hartanto on 21/11/24.
//

#ifndef MOVEGEN_H
#define MOVEGEN_H
#include "data.h"

namespace Cattris {
    class Board;
    class CollisionMap;
    class MoveGenMap;
    class Piece;

    class MoveGenMap {
    public:
        bool map[4][10][25];

    public:
        MoveGenMap();

    public:
        void clear();
        void set(const i8 x, const i8 y, ROTATION r);
        bool get(const i8 x, const i8 y, ROTATION r);
        ui8 populate(const CollisionMap& colmap, PIECE piece);
    };

}
#endif //MOVEGEN_H
