#include "movegen.h"
#include "board.h"
#include "piece.h"
#include "colmap.h"

namespace Cattris {
    void MovegenMap::set(const Rotation r, const int8_t x, const int8_t y, const PieceType p) {
        this->data[r][x+CENTER[p][r][0]] |= 1ULL << y+CENTER[p][r][1];
    }

    bool MovegenMap::get(const Rotation r, const int8_t x, const int8_t y, const PieceType p) const {
        return this->data[r][x+CENTER[p][r][0]] >> y+CENTER[p][r][1];
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
            ok |= this->data[r][x] ^ mask;
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
            ok |= this->data[r][x] ^ mask;
            this->data[r][x] |= mask;
        }

        for (int8_t x=8;x>=0;--x) {
            uint32_t mask = this->data[r][x+1] & ~colmap.column(r,x);
            ok |= this->data[r][x] ^ mask;
            this->data[r][x] |= mask;
        }
        return ok;
    }

    bool MovegenMap::rotate(Rotation r, const CollisionMap &colmap) {
        bool ok = false;

        //cw

        // TODO shift the board the kick coords, and then not with colmap, SIMD-able :D

        //ccw
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
        mask = byteswap(byteChunk);
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

        return moves;
    }
}
