#include "movegen.h"
#include "board.h"
#include "piece.h"
#include "colmap.h"

namespace Cattris {
    void MovegenMap::set(Rotation r,int8_t x, int8_t y, PieceType p) {
        this->data[r][x+CENTER[p][r][0]][y+CENTER[p][r][1]] = true;
    }

    bool MovegenMap::get(Rotation r, int8_t x, int8_t y, PieceType p) {
        return this->data[r][x+CENTER[p][r][0]][y+CENTER[p][r][1]];
    }

    bool MovegenMap::get(Move m) {
        return this->data[m.facing][m.x+CENTER[m.type][m.facing][0]][m.y+CENTER[m.type][m.facing][1]];
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

    bool Move::moveCCW(CollisionMap &colmap) {
        auto kicks = CCW_KICK_DATA[this->type==PieceType::I][this->facing];
        this->facing = Rotation((this->facing + 3) % 4);
        for (uint8_t i=0;i<5;++i) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing,this->type)) {
                this->x += kicks[i][0];
                this->y += kicks[i][1];
                return true;
            }
        }
        this->facing = Rotation((this->facing+1)%4);
        return false;
    }

    bool Move::moveCW(CollisionMap &colmap) {
        auto kicks = CW_KICK_DATA[this->type==PieceType::I][this->facing];
        this->facing = Rotation((this->facing + 1) % 4);
        for (uint8_t i=0;i<5;++i) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing,this->type)) {
                this->x += kicks[i][0];
                this->y += kicks[i][1];
                return true;
            }
        }
        this->facing = Rotation((this->facing+3)%4);
        return false;
    }

    vector<Move> Moves(Board& board, Piece& piece) {
        vector<Move> moves;
        moves.reserve(256);

        CollisionMap colmap;
        colmap.populate(board, piece.piece);

        MovegenMap map;
        MovegenMap result;

        vector<Move> queue;
        queue.reserve(128);
        queue.emplace_back(Rotation::North,3,20,piece.piece);

        while(!queue.empty()) {
            Move cur = queue.back();
            queue.pop_back();
            if (!colmap.colliding(cur.x-1,cur.y,cur.facing,piece.piece)&&!map.get(cur.facing,cur.x-1,cur.y,piece.piece)) {
                map.set(cur.facing,cur.x-1,cur.y,piece.piece);
                queue.emplace_back(cur.facing,cur.x-1,cur.y,piece.piece);
            }

            if (!colmap.colliding(cur.x+1,cur.y,cur.facing,piece.piece)&&!map.get(cur.facing,cur.x+1,cur.y,piece.piece)) {
                map.set(cur.facing,cur.x+1,cur.y,piece.piece);
                queue.emplace_back(cur.facing,cur.x+1,cur.y,piece.piece);
            }

            Move ccw = cur;
            if (ccw.moveCCW(colmap) && !map.get(ccw.facing,ccw.x,ccw.y,piece.piece)) {
                map.set(ccw.facing,ccw.x,ccw.y,piece.piece);
                queue.emplace_back(ccw.facing,ccw.x,ccw.y,piece.piece);
            }

            Move cw = cur;
            if (cw.moveCW(colmap) && !map.get(cw.facing,cw.x,cw.y,piece.piece)) {
                map.set(cw.facing,cw.x,cw.y,piece.piece);
                queue.emplace_back(cw.facing,cw.x,cw.y,piece.piece);
            }

            cur.y = colmap.height(cur.facing,cur.x,cur.y,piece.piece)-CENTER[piece.piece][cur.facing][1];
            if (!map.get(cur.facing,cur.x,cur.y,cur.type) ) {
                map.set(cur.facing,cur.x,cur.y,piece.piece);
                queue.emplace_back(cur.facing,cur.x,cur.y,piece.piece);
            }

            cur.normalize();
            if (!result.get(cur.facing,cur.x,cur.y,piece.piece)) {
                result.set(cur.facing,cur.x,cur.y,piece.piece);
                moves.emplace_back(cur.facing,cur.x,cur.y,piece.piece);
            }
        }
        return moves;
    }
}
