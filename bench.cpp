//
// Created by admin on 11/13/2024.
//
#include "board.h"
#include "piece.h"

namespace Cattris {
    long long CollisionMap::benchColmap(Board board,PIECE piece, int runs){
        int tot = 0;
        auto now = chrono::high_resolution_clock::now();
        do {
            this->populate(board, piece);
            ++tot;
        } while (tot < runs);
        auto end = chrono::high_resolution_clock::now();
        using namespace chrono;
        for (int i=0;i<4;i++) {
            cout << piece_to_string(piece) << endl;
            this->print(i);
        }
        return (duration_cast<nanoseconds>(end-now).count())/runs;
    }

    long long CollisionMap::benchColmapAllPieces(Board board, int runs) {
        long long tot = 0;
        auto piece = PIECE::NOTHING;

#define ben tot += benchColmap(board,piece,runs)
#define set piece= Cattris::PIECE::
        set I; ben; set T; ben; set S; ben; set Z; ben; set O; ben; set L; ben; set J; ben;
#undef ben
#undef set

        cout << "It took me " << tot / 7 << " ns on average to run for each piece." << endl;
        return tot;
    }
}