//
// Created by Maximus Hartanto on 21/11/24.
//

#include "movegen.h"
#include "board.h"

namespace Cattris {
    void MoveGenMap::clear() {
        memset(this->map, 0, sizeof this->map);
    }

    void MoveGenMap::set(const i8 x, const i8 y, ROTATION r, bool &value) {
        this->map[r][y] |= (ui16(value) << 9) >> x;
    }

    bool MoveGenMap::get(const i8 x, const i8 y, ROTATION r) {
        return this->map[r][y] & (1ULL << 9) >> x;
    }

    void MoveGenMap::loadHorizontalCollisionMap(const CollisionMap &colmap,ui16 ar[4][25]) {
        for (ui8 rot=0;rot<4;++rot) {
            for (ui8 x=0;x<10;++x) {
                for (ui8 y=0;y<25;++y) {
                    ar[rot][y] |= (colmap.colliding(x,y,(ROTATION)rot) << 9) >> x;
                }
            }
        }
    }

    ui8 MoveGenMap::populate(const CollisionMap &colmap, PIECE piece) {
        ui16 horizontalColmap[4][25];
        loadHorizontalCollisionMap(colmap,horizontalColmap);
        //flood fill, then run a kick check from each position and move left down right, then from that a directed graph is made.
        //from each point of the floodfill then traverse the graph (this is quite computationally expensive...)
        //the floodfill alone can be done with bitmasks and iteration
        //and because we are jumping from board to board by rotating the graph data structure must handle that too
    }

}
