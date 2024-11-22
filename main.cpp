#include <thread>
#include <chrono>
#include "piece.h"
#include "queue.h"
#include "board.h"

using namespace std;
using namespace Cattris;

int main() {
    Board board;
    CollisionMap colmap;
    board.setBigString(
        ""
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "0000000000"
        "1111111100"
        "1111111001",0
    );
    colmap.populate(board,PIECE::S);
    board.print();
    for (int i=0;i<4;i++) {
        colmap.print(i);
    }

    auto piece = Piece(3,19,PIECE::S,ROTATION::NORTH);
    piece.moveCCW(colmap);
    for (int i=0;i<100000;i++) {
        piece.moveRight(colmap);
    }
}