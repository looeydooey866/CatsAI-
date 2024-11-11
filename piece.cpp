#include "piece.h"
#include "board.h"
#include "data.h"
using namespace std;

bool Cattris::Piece::operator==(const Piece& other) {
    return (this -> piece == other.piece && this -> x == other.x && this -> y == other.y && this -> facing == other.facing);
}

// TODO do movement testing wtih adn without the collision map provided


