//
// Created by Maximus Hartanto on 21/11/24.
//

#include "movegen.h"
#include "board.h"

namespace Cattris {
    void MoveGenMap::clear() {
        memset(this->map, 0, sizeof this->map);
    }

    void MoveGenMap::set(const i8 x, const i8 y, ROTATION r) {
        this->map[r][x][y]=true;
    }

    bool MoveGenMap::get(const i8 x, const i8 y, ROTATION r) {
        return this->map[r][x][y];
    }

    ui8 MoveGenMap::populate(const CollisionMap &colmap, PIECE piece) {
        // auto chacha = [&](const i8 &px, const i8 &py, ROTATION rot) -> bool{
        //     for (i8 y=py;y>=0;y--) {
        //         for (i8 x=1;x<10;x++) {
        //             if (get(x,y,rot) && !colmap.colliding(x-1,y,rot,piece)) {
        //
        //             }
        //         }
        //     }
        // };
    }

}
