#include "movegen.h"
#include "board.h"
#include "piece.h"
#include "colmap.h"

namespace Cattris {
    void MovegenMap::set(const Rotation r, const int8_t x, const int8_t y, const PieceType p) {
        this->data[r][x + CENTER[p][r][0]] |= 1ULL << (y + CENTER[p][r][1]);
    }

    bool MovegenMap::get(const Rotation r, const int8_t x, const int8_t y, const PieceType p) const {
        return this->data[r][x + CENTER[p][r][0]] >> (y + CENTER[p][r][1]);
    }

    bool MovegenMap::get(Move m) const {
        return get(m.facing, m.x, m.y, m.type);
    }

    uint32_t MovegenMap::column(const Rotation r, const int8_t x) const {
        return this->data[r][x];
    }

    void MovegenMap::softdrop(CollisionMap &colmap) {
        for (uint8_t r = 0; r < 4; ++r) {
            for (uint8_t x = 0; x < 10; ++x) {
                uint32_t mask;
                do {
                    mask = this->data[r][x];
                    this->data[r][x] |= (mask >> 1) & ~colmap.map[r][x];
                } while (mask != this->data[r][x]);
            }
            // for (uint8_t x=0;x<10;++x) {
            //     flip(this->data[r][x]);
            //     flip(colmap.map[r][x]);
            // }
            //
            // for (uint8_t x=0;x<10;++x) {
            //     uint32_t bot = (this->data[r][x] ^ (this->data[r][x] >> 1)) & this->data[r][x];
            //     uint32_t mask = (colmap.map[r][x] & (~colmap.map[r][x] + bot)) - bot;
            //     this->data[r][x] |= mask;
            // }
            //
            // for (uint8_t x=0;x<10;++x) {
            //     flip(this->data[r][x]);
            //     flip(colmap.map[r][x]);
            // }
        }
    }

    void MovegenMap::spread(const CollisionMap &colmap) {
        for (uint8_t r = 0; r < 4; ++r) {
            for (uint8_t x = 1; x < 10; ++x) {
                this->data[r][x] |= this->data[r][x - 1] & ~colmap.map[r][x];
            }

            for (int8_t x = 8; x >= 0; --x) {
                this->data[r][x] |= this->data[r][x + 1] & ~colmap.map[r][x];
            }
        }
    }

    void MovegenMap::rotate(const CollisionMap &colmap, const PieceType p) {
        // auto shiftright = [&](uint32_t x[4][10]) {
        //     uint32_t temp[10];
        //     memcpy(temp,x[3],sizeof temp);
        //     for (uint8_t i=3;i>0;i--) {
        //        memcpy(x[i],x[i-1],sizeof x[0]);
        //     }
        //     memcpy(x[0],temp,sizeof temp);
        // };
        // auto shiftleft = [&](uint32_t x[4][10]) {
        //     uint32_t temp[10];
        //     memcpy(temp,x[0],sizeof temp);
        //     for (uint8_t i=0;i<3;i++) {
        //         memcpy(x[i],x[i+1],sizeof x[0]);
        //     }
        //     memcpy(x[3], temp, sizeof temp);
        // };
        // auto lft = [&](uint32_t x[4][10]) {
        //     for (uint8_t i=0;i<4;i++) {
        //         uint32_t temp = x[i][0];
        //         for (uint8_t a=0;a<9;a++) {
        //             x[i][a] = x[i][a+1];
        //         }
        //         x[i][9] = temp;
        //     }
        // };
        // auto rght = [&](uint32_t x[4][10]) {
        //     for (uint8_t i=0;i<4;i++) {
        //         uint32_t temp = x[i][9];
        //         for (uint8_t a=9;a>0;a--) {
        //             x[i][a] = x[i][a-1];
        //         }
        //         x[i][0] = temp;
        //     }
        // };
        // uint32_t cw[4][10];
        // uint32_t ccw[4][10];
        // memcpy(cw, this->data, sizeof cw);
        // memcpy(ccw, this->data, sizeof ccw);
        // for (uint8_t kick=0;kick<5;kick++) {
        //     int8_t osets[4][2];
        //     for (uint8_t i=0;i<4;i++) {
        //         osets[i][0] = CW_DELTA[p][i][0] + CW_KICK_DATA[p==0][i][kick][0];
        //         osets[i][1] = CW_DELTA[p][i][1] + CW_KICK_DATA[p==0][i][kick][1];
        //     }
        //     uint32_t temp[4][10];
        //     memcpy(temp,cw,sizeof temp);
        //     shiftright(temp);
        //     for (auto & oset : osets) {
        //         if (oset[0] > 0) {
        //             for (uint8_t r=0;r<oset[0];r++) {
        //                 rght(temp);
        //             }
        //         }
        //         else {
        //             for (uint8_t r=0;r<abs(oset[0]);r++) {
        //                 lft(temp);
        //             }
        //         }
        //         if (oset[1] > 0) {
        //             for (auto &board : temp) {
        //                 for (auto &col : board) {
        //                     col <<= oset[1];
        //                 }
        //             }
        //         }
        //         else {
        //             for (auto &board : temp) {
        //                 for (auto &col : board) {
        //                     col >>= abs(oset[1]);
        //                 }
        //             }
        //         }
        //     }
        // }
        if (p == PieceType::O) return;
        for (uint8_t r = 0; r < 4; r++) {
            uint32_t avail[10];
            const Rotation cw = Rotation((r + 1) % 4);
            const Rotation ccw = Rotation((r + 3) % 4);

            //cw
            memcpy(avail, this->data[r], sizeof avail);

            for (uint8_t i = 0; i < 5; ++i) {
                const int8_t xOset = CW_DELTA[p][r][0] + CW_KICK_DATA[p == 0][r][i][0];
                const int8_t yOset = CW_DELTA[p][r][1] + CW_KICK_DATA[p == 0][r][i][1];
                for (int8_t x = 0; x < 10; ++x) {
                    if (x - xOset >= 10 || x - xOset < 0) {
                        continue;
                    }
                    uint32_t col = avail[x - xOset];
                    if (yOset >= 0) {
                        col <<= yOset;
                    } else {
                        col >>= -yOset;
                    }
                    uint32_t colliding = col & colmap.map[cw][x];
                    this->data[cw][x] |= col & ~(colliding);
                    if (yOset >= 0) {
                        colliding >>= yOset;
                    } else {
                        colliding <<= -yOset;
                    }
                    avail[x - xOset] = colliding;
                }
            }

            //ccw

            memcpy(avail, this->data[r], sizeof avail);

            for (uint8_t i = 0; i < 5; ++i) {
                const int8_t xOset = CCW_DELTA[p][r][0] + CCW_KICK_DATA[p == 0][r][i][0];
                const int8_t yOset = CCW_DELTA[p][r][1] + CCW_KICK_DATA[p == 0][r][i][1];

                for (int8_t x = 0; x < 10; ++x) {
                    if (x - xOset >= 10 || x - xOset < 0) {
                        continue;
                    }
                    uint32_t col = avail[x - xOset];
                    if (yOset >= 0) {
                        col <<= yOset;
                    } else {
                        col >>= -yOset;
                    }
                    uint32_t colliding = col & colmap.map[ccw][x];
                    this->data[ccw][x] |= col & ~(colliding);
                    if (yOset >= 0) {
                        colliding >>= yOset;
                    } else {
                        colliding <<= -yOset;
                    }
                    avail[x - xOset] = colliding;
                }
            }
        }
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
                (byteChunk >> 24 & 0x000000FF) |
                (byteChunk >> 8 & 0x0000FF00) |
                (byteChunk << 8 & 0x00FF0000) |
                (byteChunk << 24 & 0xFF000000);
    }

    void MovegenMap::removeDuplicates(const PieceType p) {
        if (p == PieceType::I || p == PieceType::S || p == PieceType::Z) {
            // Prune South
            for (uint8_t x = 0; x < 10; ++x) {
                this->data[Rotation::South][x] &= ~(this->data[Rotation::North][x] << 1);
            }

            // Prune West
            for (uint8_t x = 0; x < 9; ++x) {
                this->data[Rotation::West][x] &= ~(this->data[Rotation::East][x + 1]);
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
        if (type == PieceType::I || type == PieceType::S || type == PieceType::Z) {
            if (this->facing == Rotation::South) {
                this->facing = Rotation::North;
                this->y--;
            }
            if (this->facing == Rotation::West) {
                this->facing = Rotation::East;
                this->x--;
            }
        } else if (type == PieceType::O) {
            this->facing = Rotation::North;
        }
    }

    //12 + 17 + 12 + 19 =

    vector<Move> Moves(Board &board, const Piece &piece) {
        vector<Move> moves;
        moves.reserve(256);

        CollisionMap colmap;
        colmap.populate(board, piece.piece);

        if (colmap.colliding(piece)) {
            return {};
        }

        MovegenMap pieces;
        pieces.set(piece.facing, piece.x, piece.y, piece.piece);

        //initialise with srs kick 0, each column, spread and sd, check if any are required to search again
        pieces.softdrop(colmap);
        pieces.spread(colmap);
        pieces.rotate(colmap, piece.piece);

        pieces.removeDuplicates(piece.piece);
        //bottleneck, isolate each bit
        for (uint8_t rot = 0; rot < 4; ++rot) {
            for (uint8_t x = 0; x < 10; ++x) {
                pieces.data[rot][x] &= colmap.map[rot][x] << 1 | 1;
                for (uint8_t y = 0; y < 32; ++y) {
                    if (pieces.data[rot][x] >> y & 1ULL) {
                        moves.emplace_back(Rotation(rot), x - CENTER[piece.piece][rot][0],
                                           y - CENTER[piece.piece][rot][1], piece.piece);
                    }
                }
            }
        }
        return moves;
    }
}
