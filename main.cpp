#include <thread>
#include <chrono>
#include "piece.h"
#include "queue.h"
#include "board.h"

using namespace std;

int main() {
    Cattris::Board board;
    Cattris::CollisionMap colmap{};
    board.setBigString(
        "0001110000"
        "1001111000"
        "1000111111"
        "1101111111",0);
    colmap.populate(board,Cattris::PIECE::T);
    Cattris::Piece player = Cattris::Piece(3,19,Cattris::PIECE::T,Cattris::ROTATION::NORTH);
    for (int i=0;i<10000;i++) {
        player.moveLeft(colmap);
    }
    player.moveCW(colmap);
    player.moveSD(colmap);
    player.moveCW(colmap);
    Cattris::TSPIN ret = board.isTspin(player);
    if (ret==Cattris::TSPIN::NORMAL) {
        cout << "a regular tspin has been detected burhhhh" << endl;
    }
    board.place(player);
    cout << "There are " << (int)board.fullLines() << " full lines on the board" << endl;
    board.print();
}