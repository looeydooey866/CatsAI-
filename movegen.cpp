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

    void MoveGenMap::set(const i8 x, const i8 y, ROTATION r, bool &value) {
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

    ui8 MoveGenMap::populateTest(CollisionMap &colmap, PIECE piece) {
        auto searcherSet = [&](ui16 ar[25],i8 x, i8 y) {
            ar[y] |= (1 << 9) >> x;
        };

        ui8 res=0;

        const ui16 IGNOREMAP = (1ULL << 10) - 1;

        ui16 hColmap[4][25] = {0};
        loadHorizontalCollisionMap(colmap,hColmap, piece);
        // for (ui8 i=0;i<4;++i) {
        //     for (int j=24;j>=0;--j) {
        //         cout << (int)hColmap[i][j] << endl;
        //     }
        //     cout << "=============" << endl;
        // }
        if (colmap.colliding(3,20,ROTATION::NORTH, piece)) {
            return 0;
        }
        ui16 searcher[25] = {0};
        ui16 newSearcher[25] = {0};
        Piece spawn = Piece(3,20,piece,ROTATION::NORTH);
        for (ui8 rot=0;rot<4;++rot) {
            if (rot) spawn.moveCW(colmap);
            memset(searcher,0,sizeof searcher);
            memset(newSearcher,0,sizeof searcher);
            searcherSet(searcher,spawn.x+PIECE_COORDINATES[piece][rot][0][0],spawn.y+PIECE_COORDINATES[piece][rot][0][1]);
            ui16 unequal = 0ULL;
            do{
                unequal = 0;
                for (ui8 y=0;y<24;++y) {
                    newSearcher[y] = (newSearcher[y] | (((searcher[y]<<1 | searcher[y]>>1)&IGNOREMAP) | searcher[y+1])) & ~hColmap[rot][y];
                    unequal |= newSearcher[y]^searcher[y];
                    searcher[y] |= newSearcher[y];
                }
            } while (unequal);
            for (const unsigned short i : searcher) {
                res+=__builtin_popcount(i);
            }
            memcpy(this->map[rot],searcher,sizeof(searcher));
        }
        return res;
    }
}
