//
// Created by Maximus Hartanto on 21/11/24.
//

#include "movegen.h"
#include "board.h"
#include "piece.h"

namespace Cattris {
    void MoveGenMap::clear() {
        memset(this->map, 0, sizeof this->map);
    }

    void MoveGenMap::set(const i8 x, const i8 y, ROTATION r, bool value) {
        this->map[r][y] |= (ui16(value) << 9) >> x;
    }

    bool MoveGenMap::get(const i8 x, const i8 y, ROTATION r) {
        return (this->map[r][y] >> (9 - x)) & 1ULL;
    }

    void MoveGenMap::loadHorizontalCollisionMap(const CollisionMap &colmap,ui16 ar[4][25], PIECE piece) {
        for (ui8 rot=0;rot<4;++rot) {
            for (ui8 x=0;x<10;++x) {
                for (ui8 y=0;y<25;++y) {
                    ar[rot][y] |= (colmap.colliding(x,y,(ROTATION)rot,piece) << 9) >> x;
                }
            }
        }
    }

    ui8 MoveGenMap::populateTest(CollisionMap &colmap, ui16 hColmap[4][25], PIECE piece) {
        if (colmap.colliding(3,20,ROTATION::NORTH, piece)) {
            return 0;
        }
        const ui16 IGNOREMASK = (1ULL << 10) - 1;
        Piece spawn = Piece(3,20,piece,ROTATION::NORTH);
        for (ui8 rot=0;rot<4;++rot) {
            memset(this->map[rot],0,sizeof this->map[rot]);
            if (rot) spawn.moveCW(colmap);
            set(spawn.x+PIECE_COORDINATES[piece][rot][0][0],spawn.y+PIECE_COORDINATES[piece][rot][0][1],ROTATION(rot),1);
            ui16 unequal = 0ULL;
            do{
                unequal = 0;
                for (ui8 y=0;y<24;++y) {
                    ui16 mask = (this->map[rot][y] | (((this->map[rot][y]<<1 | this->map[rot][y]>>1)&IGNOREMASK) | this->map[rot][y+1])) & ~hColmap[rot][y];
                    unequal |= mask^this->map[rot][y];
                    this->map[rot][y] |= mask;
                }
            } while (unequal);
        }
        return 0;
    }
}
