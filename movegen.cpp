#include "movegen.h"
#include "board.h"
#include "piece.h"
#include "colmap.h"

namespace Cattris {
    void MovegenMap::set(Rotation r,int8_t x, int8_t y, PieceType p) {
        this->data[r][x+CENTER[p][r][0]] |= 1ULL << y+CENTER[p][r][1];
    }

    bool MovegenMap::get(Rotation r, int8_t x, int8_t y, PieceType p) const {
        return this->data[r][x+CENTER[p][r][0]] >> y+CENTER[p][r][1];
    }

    bool MovegenMap::get(Move m) const {
        return get(m.facing,m.x,m.y,m.type);
    }

    uint32_t MovegenMap::column(Rotation r, int8_t x) const {
        return this->data[r][x];
    }

    void MovegenMap::softdrop(Rotation r, CollisionMap &colmap) {
        bool ok = false;
        for (uint8_t x=0;x<10;++x) {
            flip(this->data[r][x]);
            flip(colmap.map[r][x]);

            uint32_t bot = (this->data[r][x] ^ (this->data[r][x] >> 1)) & this->data[r][x];
            this->data[r][x] |= (colmap.map[r][x] & (~colmap.map[r][x] + bot)) - bot;

            flip(this->data[r][x]);
            flip(colmap.map[r][x]);
        }
    }

    void MovegenMap::spread(Rotation r, CollisionMap &colmap) {
        for (uint8_t x=1;x<10;++x) {
            this->data[r][x] |= this->data[r][x-1] & ~colmap.column(r,x);
        }

        for (int8_t x=8;x>=0;--x) {
            this->data[r][x] |= this->data[r][x+1] & ~colmap.column(r,x);
        }
    }

    void flip(uint32_t &mask) {
        uint32_t byteChunk =
            (mask >> 3 & 0x11111111) |
            (mask >> 1 & 0x22222222) |
            (mask << 1 & 0x44444444) |
            (mask << 3 & 0x88888888);
        mask = byteswap(byteChunk);
    }

    void MovegenMap::removeDuplicates(PieceType p) {
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

    Move::Move(Rotation r, int8_t x, int8_t y, PieceType p) {
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

    vector<Move> Moves(Board& board, Piece& piece) {
        vector<Move> moves;
        moves.reserve(256);

        CollisionMap colmap;
        colmap.populate(board, piece.piece);

        MovegenMap pieces;
        pieces.set(piece.facing,piece.x,piece.y,piece.piece);


        return moves;
    }
}
