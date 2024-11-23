#include <thread>
#include <chrono>
#include "piece.h"
#include "queue.h"
#include "board.h"
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

    MoveGenMap map;
    using namespace chrono;
    ui32 ctr=0;
    auto now = high_resolution_clock::now();
    do {
        map.populateTest(colmap, PIECE::S);
        ++ctr;
    } while(duration_cast<milliseconds>(high_resolution_clock::now()-now).count()<1000);
    for (int i=0;i<4;i++) {
        for (int j=24;j>=0;j--) {
            cout << bitset<10>((int)map.map[i][j]) << endl;
        }
        if (3-i) cout << "\n==============\n";
    }
    cout << ">===" << ctr << "===<" << endl;
}