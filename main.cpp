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
    board.setBigString(DT_CANNON_BAD,0);
    fancyprint(board.board);
    Piece test = Piece(3,20,PieceType::T,Rotation::North);
    benchMovegen(board,test);
}