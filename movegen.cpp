#include "movegen.h"
#include "board.h"
#include "piece.h"
#include "colmap.h"

namespace Cattris {
    void MovegenMap::set(const Rotation r, const int8_t x, const int8_t y, const PieceType p) {
        this->data[r][x+CENTER[p][r][0]] |= 1ULL << (y+CENTER[p][r][1]);
    }

    bool MovegenMap::get(const Rotation r, const int8_t x, const int8_t y, const PieceType p) const {
        return this->data[r][x+CENTER[p][r][0]] >> (y+CENTER[p][r][1]);
    }

    bool MovegenMap::get(Move m) const {
        return get(m.facing,m.x,m.y,m.type);
    }

    uint32_t MovegenMap::column(const Rotation r, const int8_t x) const {
        return this->data[r][x];
    }

    bool MovegenMap::softdrop(const Rotation r, CollisionMap &colmap) {
        bool ok = false;
        for (uint8_t x=0;x<10;++x) {
            flip(this->data[r][x]);
            flip(colmap.map[r][x]);
        }

        for (uint8_t x=0;x<10;++x) {
            uint32_t bot = (this->data[r][x] ^ (this->data[r][x] >> 1)) & this->data[r][x];
            uint32_t mask = (colmap.map[r][x] & (~colmap.map[r][x] + bot)) - bot;
            ok |= (mask & ~(this->data[r][x]))!=0ULL;
            this->data[r][x] |= mask;
        }

        for (uint8_t x=0;x<10;++x) {
            flip(this->data[r][x]);
            flip(colmap.map[r][x]);
        }
        return ok;
    }

    bool MovegenMap::spread(const Rotation r, const CollisionMap &colmap) {
        bool ok = false;
        for (uint8_t x=1;x<10;++x) {
            uint32_t mask = this->data[r][x-1] & ~colmap.column(r,x);
            ok |= (mask & ~(this->data[r][x])) != 0ULL;
            this->data[r][x] |= mask;
        }

        for (int8_t x=8;x>=0;--x) {
            uint32_t mask = this->data[r][x+1] & ~colmap.column(r,x);
            ok |= (mask & ~(this->data[r][x]))!=0ULL;
            this->data[r][x] |= mask;
        }
        return ok;
    }

    bool MovegenMap::rotate(Rotation r, const CollisionMap &colmap, const PieceType p) {
        bool ok = false;
        uint32_t before[4][10];
        memcpy(before, this->data, sizeof before);
        uint32_t avail[10];
        const Rotation cw = Rotation((r+1)%4);
        const Rotation ccw = Rotation((r+3)%4);

        //cw
        memcpy(avail,this->data[r],sizeof avail);

        for (uint8_t i=0;i<5;++i) {
            const int8_t xOset = CW_DELTA[p][r][0] + CW_KICK_DATA[p==0][r][i][0];
            const int8_t yOset = CW_DELTA[p][r][1] + CW_KICK_DATA[p==0][r][i][1];
            const int8_t posy = (yOset>0?yOset:0);
            const int8_t negy = (yOset<0?abs(yOset):0);
            const int8_t start = (xOset>0?xOset:0);
            const int8_t end = (xOset<0?10+xOset:10);
#define iter for (int8_t x=start;x<end;++x)
            uint32_t cols[10];
            iter{
                cols[x] = (avail[x-xOset]<<posy)>>negy;
                this->data[cw][x] |= cols[x] & ~(colmap.map[cw][x]);
                avail[x-xOset] = ((cols[x]&colmap.map[cw][x])>>posy)<<negy;
            }
        }

        //ccw

        memcpy(avail, this->data[r], sizeof avail);

        for (uint8_t i=0;i<5;++i) {
            const int8_t xOset = CCW_DELTA[p][r][0] + CCW_KICK_DATA[p==0][r][i][0];
            const int8_t yOset = CCW_DELTA[p][r][1] +  CCW_KICK_DATA[p==0][r][i][1];
            const int8_t start = (xOset>0?xOset:0);
            const int8_t end = (xOset<0?10+xOset:10);
            for (int8_t x = start; x < end; ++x) {
                uint32_t col = avail[x-xOset];
                if (yOset >= 0) {
                    col <<= yOset;
                }
                else {
                    col >>= -yOset;
                }
                uint32_t colliding = col & colmap.map[ccw][x];
                this->data[ccw][x] |= col & ~(colliding);
                if (yOset >= 0) {
                    colliding >>= yOset;
                }
                else {
                    colliding <<= -yOset;
                }
                avail[x-xOset] = colliding;
            }
        }
        for (uint8_t i=0;i<4;i++) {
            for (uint8_t x=0;x<10;x++) {
                if (before[i][x] != this->data[i][x]) {
                    ok = true;
                    break;
                }
            }
        }
        return ok;
    }

    void flip(uint32_t &mask) {
        uint32_t byteChunk =
            (mask >> 7 & 0x01010101) |
            (mask >> 5 & 0x02020202) |
            (mask >> 3 & 0x04040404) |
            (mask >> 1 & 0x08080808) |
            (mask << 1 & 0x10101010) |
            (mask << 3 & 0x20202020) |
            (mask << 5 & 0x40404040) |
            (mask << 7 & 0x80808080);
        mask =
        (byteChunk>>24 & 0x000000FF) |
        (byteChunk>>8  & 0x0000FF00) |
        (byteChunk<<8  & 0x00FF0000) |
        (byteChunk<<24 & 0xFF000000);
    }

    void MovegenMap::removeDuplicates(const PieceType p) {
        if (p==PieceType::I||p==PieceType::S||p==PieceType::Z) {
            // Prune South
            for (uint8_t x=0;x<10;++x) {
                this->data[Rotation::South][x] &= ~(this->data[Rotation::North][x] << 1);
            }

            // Prune West
            for (uint8_t x=0;x<9;++x) {
                this->data[Rotation::West][x] &= ~(this->data[Rotation::East][x+1]);
            }
        }
    }

    Move::Move(const Rotation r, const int8_t x, const int8_t y, const PieceType p) {
        this->facing = r;
        this->x = x;
        this->y = y;
        this->type = p;
    }

    void Move::normalize() {
        if (type==PieceType::I||type==PieceType::S||type==PieceType::Z) {
            if (this->facing==Rotation::South) {
                this->facing=Rotation::North;
                this->y--;
            }
            if (this->facing==Rotation::West) {
                this->facing=Rotation::East;
                this->x--;
            }
        }
        else if (type==PieceType::O) {
            this->facing=Rotation::North;
        }
    }
    //12 + 17 + 12 + 19 =

    vector<Move> Moves(Board& board, const Piece& piece) {
        vector<Move> moves;
        moves.reserve(256);

        CollisionMap colmap;
        colmap.populate(board, piece.piece);

        if (colmap.colliding(piece)) {
            return {};
        }

        MovegenMap pieces;
        pieces.set(piece.facing,piece.x,piece.y,piece.piece);

        bool gogogo = false;
        do {
            gogogo = false;
            for (uint8_t i = 0; i < 4; i++) {
                gogogo |= pieces.softdrop(Rotation(i), colmap);
                gogogo |= pieces.spread(Rotation(i), colmap);
                gogogo |= pieces.rotate(Rotation(i),colmap,piece.piece);
            }
        } while(gogogo);

        pieces.removeDuplicates(piece.piece);
        for (uint8_t rot=0;rot<4;++rot) {
            for (uint8_t x=0;x<10;++x) {
                pieces.data[rot][x] &= colmap.map[rot][x] << 1 | 1;
                for (uint8_t y=0;y<32;++y) {
                    if (pieces.data[rot][x]>>y&1ULL) {
                        moves.emplace_back(Rotation(rot),x-CENTER[piece.piece][rot][0],y-CENTER[piece.piece][rot][1],piece.piece);
                    }
                }
            }
        }
        return moves;
    }

}
