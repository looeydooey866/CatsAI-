#include "board.h"
#include "piece.h"
#include "colmap.h"
#include "movegen.h"

namespace Cattris {
    long long CollisionMap::benchColmap(Board& board, PieceType piece, int runs){
        int tot = 0;
        auto now = chrono::high_resolution_clock::now();
        vector<thread> v;
        do {
            this->populate(board, piece);
            ++tot;
        } while (tot < runs);
        auto end = chrono::high_resolution_clock::now();
        using namespace chrono;
        // for (int i=0;i<4;i++) {
        //     cout << piece_to_string(piece) << endl;
        //     this->print(i);
        // }
        return (duration_cast<nanoseconds>(end-now).count())/runs;
    }

    long long CollisionMap::benchColmapAllPieces(Board& board, int runs) {
        long long tot = 0;
        auto piece = PieceType::Nothing;

#define ben tot += benchColmap(board,piece,runs)
#define set piece= Cattris::PieceType::
        set I; ben; set T; ben; set S; ben; set Z; ben; set O; ben; set L; ben; set J; ben;
#undef ben
#undef set

        cout << "It took me " << tot / 7 << " ns on average to run for each piece." << endl;
        return tot;
    }

    long long benchMovegen(Board &board, Piece &piece) {
        long long ctr = 0;
        long long nodes = 0;
        auto now = chrono::high_resolution_clock::now();
        do {
            ++ctr;
            nodes += Moves(board, piece).size();
        } while (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - now).count() < 1000)
        ;
        cout << "I ran the function " << ctr << " times.\nIt generated " << nodes << " nodes in a second.\n";
        cout << "In the board, there are " << int(Moves(board, piece).size()) <<" available moves."<< "\n";
        return nodes;
    }


}
