#include <thread>
#include <chrono>
#include "piece.h"
#include "board.h"
#include "colmap.h"
#include "movegen.h"

using namespace std;
using namespace Cattris;

int main() {
    Board board;
    CollisionMap colmap;
    board.setBigString(
        ""
        "0000000000"
        "0000000000"
        "0000000001"
        "0000000000"
        "1111111110"
        "0000000000"
        "0000000000"
        "0011111111"
        "0001111111"
        "1101111111"
        "1001111111"
        "1000111111"
        "1101111111"
        "1101111111",0
    );
    colmap.populate(board,PieceType::T);
    Piece test = Piece(3,20,PieceType::T,Rotation::North);
    benchMovegen(board,test);
}