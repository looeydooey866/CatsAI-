//
// Created by admin on 11/25/2024.
//

#include "data.h"
#include "colmap.h"

namespace Cattris {
    void CollisionMap::populate(Board &board, PieceType piece) {
        memset(this->map,0,sizeof(this->map));
        uint32_t MAX_MASK = ~uint32_t(0);
        for (uint8_t rot = 0; rot < PieceType_SYMMETRY[piece]; ++rot) {
            for (uint8_t mino = 0; mino < 4; ++mino) {
                int8_t xOset = CENTER_OSETS[piece][rot][mino][0];
                int8_t yOset = CENTER_OSETS[piece][rot][mino][1];
                for (uint8_t x = 0; x < 10; ++x) {
                    this->map[rot][x] |= ( (x+xOset >= 10) ? MAX_MASK : ( (yOset >= 0) ? board.board[x + xOset] >> yOset : ((1ULL << abs(yOset)) - 1) | board.board[x + xOset] << abs(yOset) ) );
                }
            }
        }
        for (uint8_t rot = PieceType_SYMMETRY[piece]; rot < 4; ++rot) {
            memcpy(this->map[rot],this->map[rot%PieceType_SYMMETRY[piece]],sizeof(this->map[0]));
        }
    }

    bool CollisionMap::colliding(int8_t x,int8_t y, Rotation rot, PieceType piece) const{
        x += CENTER[piece][rot][0];
        y += CENTER[piece][rot][1];
        return (x < 0 || x >= 10 || y < 0) || (((this->map[rot][x]>>y)&1));
    }

    bool CollisionMap::colliding(Piece &p) const{
        return this->map[p.facing][p.x+PIECE_COORDINATES[p.piece][p.facing][0][0]]>>(p.y+PIECE_COORDINATES[p.piece][p.facing][0][1])&1;
    }

    uint32_t CollisionMap::column(Rotation rot, int8_t x) const {
        return this->map[rot][x];
    }

    uint8_t CollisionMap::height(Rotation rot,int8_t x, int8_t y, PieceType piece) {
        return 32 - countl_zero(((1 << y+CENTER[piece][rot][1]) - 1) & this->map[rot][x+CENTER[piece][rot][0]]);
    }

    void CollisionMap::getHeightArray(Rotation rot, uint8_t height[10], PieceType piece) {
        for (uint8_t i=0;i<10;i++) {
            height[i] = uint8_t(32-countl_zero(this->map[rot][i]));
        }
    }

    void CollisionMap::print(int rot) {
        string ret;
        for (int i=0;i<10;i++) {
            ret += "+";
            ret += "---";
        }
        ret += "+\n";
        for (int i = 24; i >= 0; i--) {
            ret += "| ";
            for (int j = 0; j < 10; j++) {
                ret += (this->map[rot][j] >> i & 1 ? "#" : ".");
                if (9 - j) ret += " | ";
            }
            ret += " |";
            ret += "\n";
            ret += "+";
            for (int j=0;j<10;j++) {
                ret += "---";
                ret += "+";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }
} // Cattris