#include "piece.h"
#include "board.h"
#include "data.h"
using namespace std;
#define LOOEYDEBUG

namespace Cattris {
    bool Piece::operator==(const Piece& other) {
        return (this -> piece == other.piece && this -> x == other.x && this -> y == other.y && this -> facing == other.facing);
    }

    Piece::Piece() {
        this->x = 3;
        this->y = 17;
        this->piece=PIECE::NOTHING;
        this->facing=ROTATION::NORTH;
    }

    Piece::Piece(i8 x, i8 y, PIECE p, ROTATION r) {
        this->x=x;
        this->y=y;
        this->piece=p;
        this->facing=r;
    }

    bool Piece::moveLeft(CollisionMap &colmap) {
        if (this->x + PIECE_COORDINATES[this->piece][this->facing][0][0]!= 0 && !colmap.colliding(this->x-1,this->y,this->facing)) {
            this->x --;
            return true;
        }
        return false;
    }

    bool Piece::moveRight(CollisionMap &colmap) {
        if (this->x + PIECE_COORDINATES[this->piece][this->facing][0][0] != 9 && !colmap.colliding(this->x+1,this->y,this->facing)) {
            this->x ++;
            return true;
        }
        return false;
    }

    bool Piece::moveCW(CollisionMap &colmap) {
        auto kicks = CW_KICK_DATA[this->piece==PIECE::I][this->facing];
        this->facing = static_cast<ROTATION>((this->facing + 1) % 4);
        for (ui8 i=0;i<5;i++) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing)) {
                this->x += i8(kicks[i][0]);
                this->y += i8(kicks[i][1]);
#ifdef LOOEYDEBUG
                cout << "Kick! " << i+1 << endl;
#endif
                return true;
            }
        }
        this->facing = static_cast<ROTATION>((this->facing+3)%4);
        return false;
    }

    bool Piece::moveCCW(CollisionMap &colmap) {
        auto kicks = CCW_KICK_DATA[this->piece == PIECE::I][this->facing];
        this->facing = static_cast<ROTATION>((this->facing + 3) % 4);
        for (ui8 i=0;i<5;i++) {
            if (!colmap.colliding(this->x+kicks[i][0],this->y+kicks[i][1],this->facing)) {
                this->x += i8(kicks[i][0]);
                this->y += i8(kicks[i][1]);
#ifdef LOOEYDEBUG
                cout << "Kick! " << i+1 << endl;
#endif
                return true;
            }
        }
        this->facing = static_cast<ROTATION>((this->facing+1)%4);
        return false;
    }

    bool Piece::moveSD(CollisionMap &colmap) {
        if (this->y +PIECE_COORDINATES[this->piece][this->facing][0][1]!= colmap.height(this->facing,this->x)) {
            this->y = colmap.height(this->facing,this->x) - PIECE_COORDINATES[this->piece][this->facing][0][1];
            return true;
        }
        return false;
    }
}