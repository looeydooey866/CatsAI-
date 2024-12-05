#include <thread>
#include <chrono>
#include "piece.h"
#include "board.h"
#include "colmap.h"
#include "movegen.h"

using namespace std;
using namespace Cattris;

// int main() {
//     Board board;
//     board.setBigString(DT_CANNON_BAD, 0);
//     fancyprint(board.board);
//     Piece test = Piece(3,20,PieceType::T,Rotation::North);
//     benchMovegen(board,test);
//
//     board.clear();
//     board.setBigString(TKI,0);
//     assert(Moves(board,test).size() == TKI_POSITIONS);
//
//     board.clear();
//     board.setBigString(MOUNTAINOUS_STACKING_2,0);
//     assert(Moves(board,test).size() == MOUNTAINOUS_STACKING_2_POSITIONS);
//
//     board.clear();
//     board.setBigString(DT_CANNON,0);
//     assert(Moves(board,test).size() == DT_CANNON_POSITIONS);
//
//     board.clear();
//     board.setBigString(DT_CANNON_BAD,0);
//     assert(Moves(board,test).size() == DT_CANNON_BAD_POSITIONS);
// }
#include <chrono>
#include <iomanip>  // for std::setw and std::setfill
#include <iostream>
#include <numeric>
#include <cmath>

char to_char(PieceType p) {
    switch (p)
    {
    case PieceType::I:
        return 'I';
    case PieceType::O:
        return 'O';
    case PieceType::T:
        return 'T';
    case PieceType::L:
        return 'L';
    case PieceType::J:
        return 'J';
    case PieceType::S:
        return 'S';
    case PieceType::Z:
        return 'Z';
    default:
        break;
    }
};

int main() {

    std::array<PieceType, 7> queue {
        // IOTLJSZ
        PieceType::I,
        PieceType::O,
        PieceType::T,
        PieceType::L,
        PieceType::J,
        PieceType::S,
        PieceType::Z
    };

    using namespace std;

    Board board;

    auto func = [&] (Board b) {
        const int count = 1000000;

        // For each piece
        for (int8_t t = 0; t < 7; ++t) {
            int64_t time = 0;
            int64_t c = 0;

            std::vector<int64_t> lists;
            lists.reserve(1000000);

            for (int i = 0; i < count; ++i) {
                auto time_start = chrono::high_resolution_clock::now();
                auto m = Moves(board,Piece(3,20,queue[t],Rotation::North));
                auto time_stop = chrono::high_resolution_clock::now();

                auto dt = chrono::duration_cast<chrono::nanoseconds>(time_stop - time_start).count();

                c += m.size();
                time += dt;
                lists.push_back(dt);
            }

            // Calculate mean time & movegen count
            time = time / count;
            c = c / count;

            // Calculate stdev
            uint64_t sd = 0;
            uint64_t max = 0;
            uint64_t min = UINT64_MAX;

            for (auto dt : lists) {
                sd += (dt - time) * (dt - time);
                max = std::max(max, uint64_t(dt));
                min = std::min(min, uint64_t(dt));
            }

            sd = sd / count;

            cout << "    piece: " << to_char(queue[t]) << "    time: " << time << " ns" << "    stdev: " << std::sqrt(sd) << "    min: " << min << " ns"  << "    max: " << max << " ns" << "    count: " << c << endl;
        }
    };

    board.board[9] = 0b00111111;
    board.board[8] = 0b00111111;
    board.board[7] = 0b00011111;
    board.board[6] = 0b00000111;
    board.board[5] = 0b00000001;
    board.board[4] = 0b00000000;
    board.board[3] = 0b00001101;
    board.board[2] = 0b00011111;
    board.board[1] = 0b00111111;
    board.board[0] = 0b11111111;

    cout << "BOARD TSPIN" << endl;
    func(board);

    board.board[9] = 0b111111111;
    board.board[8] = 0b111111111;
    board.board[7] = 0b011111111;
    board.board[6] = 0b011111111;
    board.board[5] = 0b000111111;
    board.board[4] = 0b000100110;
    board.board[3] = 0b010000001;
    board.board[2] = 0b011110111;
    board.board[1] = 0b011111111;
    board.board[0] = 0b011111111;

    cout << "BOARD DT CANNON" << endl;
    func(board);

    board.board[9] = 0b000011111111;
    board.board[8] = 0b000011000000;
    board.board[7] = 0b110011001100;
    board.board[6] = 0b110011001100;
    board.board[5] = 0b110011001100;
    board.board[4] = 0b110011001100;
    board.board[3] = 0b110011001100;
    board.board[2] = 0b110000001100;
    board.board[1] = 0b110000001100;
    board.board[0] = 0b111111111100;

    cout << "BOARD TERRIBLE" << endl;
    func(board);

    return 0;
}