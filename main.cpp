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
    colmap.benchColmapAllPieces(board,10000000);
    for (int i=0;i<4;i++) {
        colmap.print(i);
    }
}