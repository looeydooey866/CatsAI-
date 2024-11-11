//
// Created by admin on 10/9/2024.
//
#include "board.h"
#include "piece.h"

namespace Cattris {
    uint32_t& Board::operator [] (int index) {
        assert(index > -1 && index < 10);
        return this->board[index];
    }

    bool Board::operator == (const Board& other) {
        for (int i=0;i<10;i++) {
            if (this->board[i] != other.board[i]) return false;
        }
        return true;
    }

    void Board::set(const int8_t x, const int8_t y) {
        assert(y < 25);
        this->board[x] &= (static_cast<uint32_t>(1) << y);
    }

    bool Board::get(const int8_t x, const int8_t y) {
        return (this->board[x] >> y) & static_cast<uint32_t>(1);
    }

    void Board::getHeightArray(uint8_t height[10]) {
        for (int i=0;i<10;i++) {
            height[i] = 32 - countl_zero(this->board[i]);
        }
    }

    bool Board::isSet(const int8_t x, int8_t y) {
        return get(x,y);
    }

    bool Board::isTspin(Piece &p) {

    }

    uint32_t Board::getMask() {
        uint32_t mask = this->board[0];
        for (int i=1;i<10;i++) {
            mask &= this -> board[i];
        }
        return mask;
    }

    uint8_t Board::fullLines() {
        return popcount(getMask());
    }

    void Board::clearLines() {

    }

    void Board::print() {
        string ret;
        for (int i = 24; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                ret += (this->board[j] >> i & 1 ? "#" : ".");
                if (9 - j) ret += " | ";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }

    void CollisionMap::populate(Board &board, PIECE piece) {
        memset(this->map,0,sizeof(this->map));
        for (uint8_t rot=static_cast<uint8_t>(ROTATION::NORTH);rot<4;rot++) {
            for (uint8_t mino=0;mino<4;mino++) {
                //x offset and y offset, negate those
                for (uint8_t x=0;x<10;x++) {
                    if (x+CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][0] >= 10) this->map[rot][x]|=UINT32_MAX;
                    if(CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][1]>=0)this->map[rot][x]|=board.board[x+CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][0]]>>CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][1];
                    else this->map[rot][x]|=(~((~static_cast<uint32_t>(0)) << abs(CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][1]))) | board.board[x+CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][0]]<<abs(CENTER_OSETS[static_cast<uint8_t>(piece)][rot][mino][1]);
                }
            }
        }
    }

    bool CollisionMap::colliding(const int8_t x, const int8_t y, ROTATION rot, PIECE piece) {

    }

    bool CollisionMap::colliding(Piece &p) {

    }

    void CollisionMap::print(int rot) {
        string ret;
        for (int i = 24; i >= 0; i--) {
            for (int j = 0; j < 10; j++) {
                ret += (this->map[rot][j] >> i & 1 ? "#" : ".");
                if (9 - j) ret += " | ";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }

    void PosMap::clear() {

    }

    void PosMap::set(const int8_t x, const int8_t y, ROTATION r, bool value) {

    }

    bool PosMap::get(const int8_t x, const int8_t y, ROTATION r) {

    }

    void GameBoard::clear() {

    }

    void GameBoard::clearLines() {

    }

    void GameBoard::set(int x, int y, string type) {

    }
}