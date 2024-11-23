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
        ui16 map[4][25] = {0};

    public:
        void clear();
        void set(const i8 x, const i8 y, ROTATION r, bool &value);
        bool get(const i8 x, const i8 y, ROTATION r);
        void loadHorizontalCollisionMap(const CollisionMap &colmap, ui16 ar[4][25], PIECE piece);
        ui8 populateTest(CollisionMap& colmap, PIECE piece);
    };
}
#endif //MOVEGEN_H
