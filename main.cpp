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
        "1010101010"
        "1111111111"
        "1010101010"
        "0101010101"
        "1010101010"
        "0101010101",0);

}