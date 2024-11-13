#include "piece.h"
#include "board.h"
#include "data.h"
using namespace std;

namespace Cattris {
    bool Piece::operator==(const Piece& other) {
        return (this -> piece == other.piece && this -> x == other.x && this -> y == other.y && this -> facing == other.facing);
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


