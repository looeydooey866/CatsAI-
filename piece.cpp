#include "piece.h"
#include "board.h"
#include "data.h"
#include "colmap.h"
using namespace std;

namespace Cattris {
    bool Piece::operator==(const Piece& other) {
        return (this -> piece == other.piece && this -> x == other.x && this -> y == other.y && this -> facing == other.facing);
    }

    Piece::Piece() {
        this->x = 3;
        this->y = 20;
        this->piece=PieceType::Nothing;
        this->facing=Rotation::North;
    }

    Piece::Piece(int8_t x, int8_t y, PieceType p, Rotation r) {
        this->x=x;
        this->y=y;
        this->piece=p;
        this->facing=r;
    }

    uint8_t Piece::centerX() {
        return this->x + CENTER[this->piece][this->facing][0];
    }

    uint8_t Piece::centerY() {
        return this->y + CENTER[this->piece][this->facing][1];
    }

    bool Piece::moveLeft(CollisionMap &colmap) {
        if (centerX() != 0 && !colmap.colliding(this->x-1,this->y,this->facing,this->piece)) {
            this->x --;
            return true;
        }
        return false;
    }

    bool Piece::moveRight(CollisionMap &colmap) {
        if (centerX() != 9 && !colmap.colliding(this->x+1,this->y,this->facing,this->piece)) {
            this->x++;
            return true;
        }
        return false;
    }

    bool Piece::moveCW(CollisionMap &colmap) {
        auto kicks = CW_KICK_DATA[this->piece==PieceType::I][this->facing];
        this->facing = Rotation((this->facing + 1) % 4);
        for (uint8_t i=0;i<5;i++) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing,this->piece)) {
                this->x += int8_t(kicks[i][0]);
                this->y += int8_t(kicks[i][1]);
                return true;
            }
        }
        this->facing = static_cast<Rotation>((this->facing+3)%4);
        return false;
    }

    bool Piece::moveCCW(CollisionMap &colmap) {
        auto kicks = CCW_KICK_DATA[this->piece == PieceType::I][this->facing];
        this->facing = Rotation((this->facing + 3) % 4);
        for (uint8_t i=0;i<5;i++) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing,this->piece)) {
                this->x += int8_t(kicks[i][0]);
                this->y += int8_t(kicks[i][1]);
                return true;
            }
        }
        this->facing = static_cast<Rotation>((this->facing+1)%4);
        return false;
    }

    bool Piece::moveSD(CollisionMap &colmap) {
        if (centerY()!= colmap.height(this->facing,this->x,this->y,this->piece)) {
            this->y = colmap.height(this->facing,this->x,this->y,this->piece) - CENTER[this->piece][this->facing][1];
            return true;
        }
        return false;
    }

    void Piece::normalize() {
        if (this->piece==PieceType::I||this->piece==PieceType::S||this->piece==PieceType::Z) {
            if (this->facing==Rotation::South) {
                this->facing=Rotation::North;
                this->y--;
            }
            if (this->facing==Rotation::West) {
                this->facing=Rotation::East;
                this->x--;
            }
        }
        else if (this->piece==PieceType::O) {
            this->facing=Rotation::North;
        }
    }
}
