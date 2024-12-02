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
    board.setBigString(DT_CANNON_BAD, 0);
    fancyprint(board.board);
    Piece test = Piece(3,20,PieceType::T,Rotation::North);
    benchMovegen(board,test);

    board.clear();
    board.setBigString(TKI,0);
    assert(Moves(board,test).size() == TKI_POSITIONS);

    board.clear();
    board.setBigString(MOUNTAINOUS_STACKING_2,0);
    assert(Moves(board,test).size() == MOUNTAINOUS_STACKING_2_POSITIONS);

    board.clear();
    board.setBigString(DT_CANNON,0);
    assert(Moves(board,test).size() == DT_CANNON_POSITIONS);

    board.clear();
    board.setBigString(DT_CANNON_BAD,0);
    assert(Moves(board,test).size() == DT_CANNON_BAD_POSITIONS);
}