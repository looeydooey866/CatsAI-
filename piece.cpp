#include "piece.h"
#include "board.h"
#include "data.h"
using namespace std;

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

    Piece::Piece(int8_t x, int8_t y, PIECE p, ROTATION r) {
        this->x=x;
        this->y=y;
        this->piece=p;
        this->facing=r;
    }

    bool Piece::moveLeft(Board &board, CollisionMap &colmap) {
        
    }

    bool Piece::moveRight(Board &board, CollisionMap &colmap) {

    }

    bool Piece::moveCW(Board &board, CollisionMap &colmap) {

    }

    bool Piece::moveCCW(Board &board, CollisionMap &colmap) {

    }

    bool Piece::moveSD(Board &board, CollisionMap &colmap) {

    }
}

// TODO do movement testing wtih adn without the collision map provided


