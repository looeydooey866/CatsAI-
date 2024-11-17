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

    void Board::set(const int8_t& x, const int8_t &y) {
        assert(y>=0&&y<25&&x>=0&&x<10);
        this->board[x] |= (static_cast<uint32_t>(1) << y);
    }

    void Board::setfill(const int8_t &x1, const int8_t &y1, const int8_t &x2, const int8_t &y2) {
        assert(y1>=0&&y1<25&y2>=0&&y2<25&&x1>=0&&x1<10&&x2>=0&&x2<10);
        for (int8_t x=min(x1,x2);x<=max(x1,x2);x++) {
            for (int8_t y=min(y1,y2);y<=max(y1,y2);y++) {
                this->set(x,y);
            }
        }
    }

    void Board::setstring(const string s, int y) {
        cerr << s << ' ' << y << endl;
        assert(s.size()==10 && y >= 0 && y < 25);
        for (int i=0;i<10;i++) {
            if (s[i]=='1') set(i,y);
        }
    }

    void Board::setBigString(const string s, int y) {
        assert(s.size()%10==0 && y >= 0 && y + (s.size()/10) - 1 < 25);
        for (int i=0;i<s.size()/10;i++){
            this->setstring(s.substr(i*10,10),(s.size()/10-i-1)+y);
        }
    }


    bool Board::get(const int8_t &x, const int8_t &y) {
        return (this->board[x] >> y) & static_cast<uint32_t>(1);
    }

    void Board::getHeightArray(uint8_t height[10]) {
        for (int i=0;i<10;i++) {
            height[i] = 32 - countl_zero(this->board[i]);
        }
    }

    TSPIN Board::isTspin(Piece &p) {
        if (p.piece != PIECE::T) {
            return TSPIN::UNKNOWN;
        }

        uint8_t corners = 0;
        uint8_t x = p.x;
        uint8_t y = p.y;
#define BLX x+0
#define BLY y+0
#define BRX x+2
#define BRY y+0
#define TLX x+0
#define TLY y+2
#define TRX x+2
#define TRY y+0

#define try(x,y) if (x<0||x>=10||y<0||get(x,y)) corners++; \

        try(BLX,BLY);
        try(BRX,BRY);
        try(TLX,TLY);
        try(TRX,TRY);

#undef try(x,y)

        if (corners < 3) return TSPIN::UNKNOWN;

        constexpr uint8_t xFac[5] = {0,2,2,0,0};
        constexpr uint8_t yFac[5] = {2,2,0,0,2};

        uint8_t facing = get(xFac[p.facing],yFac[p.facing]) + get(xFac[p.facing+1],yFac[p.facing+1]);

        if (facing < 2) {
            return TSPIN::MINI;
        }
        else {
            return TSPIN::NORMAL;
        }
    }

    TSPIN Board::isTspin(const int8_t px, const int8_t py, ROTATION rotation, PIECE piece) {
        if (piece != PIECE::T) {
            return TSPIN::UNKNOWN;
        }

        uint8_t corners = 0;
        uint8_t x = px;
        uint8_t y = py;
#define BLX x+0
#define BLY y+0
#define BRX x+2
#define BRY y+0
#define TLX x+0
#define TLY y+2
#define TRX x+2
#define TRY y+0

#define try(x,y) if (x<0||x>=10||y<0||get(x,y)) corners++; \

        try(BLX,BLY);
        try(BRX,BRY);
        try(TLX,TLY);
        try(TRX,TRY);

#undef try(x,y)

        if (corners < 3) return TSPIN::UNKNOWN;

        constexpr uint8_t xFac[5] = {0,2,2,0,0};
        constexpr uint8_t yFac[5] = {2,2,0,0,2};

        uint8_t facing = get(xFac[rotation],yFac[rotation]) + get(xFac[rotation+1],yFac[rotation+1]);

        if (facing < 2) {
            return TSPIN::MINI;
        }
        else {
            return TSPIN::NORMAL;
        }
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
        uint32_t MAX_MASK = ~uint32_t(0);
        for (uint8_t rot=0;rot<PIECE_SYMMETRY[piece];++rot){
            for (uint8_t mino=0;mino<4;++mino) {
                for (uint8_t x=0;x<10;++x) {
                    int xOset = CENTER_OSETS[piece][rot][mino][0];
                    int yOset = CENTER_OSETS[piece][rot][mino][1];
                    if (x+xOset >= 10) {this->map[rot][x]|=MAX_MASK; continue;}
                    if(yOset>=0)this->map[rot][x]|=board.board[x+xOset]>>yOset;
                    else this->map[rot][x]|=(~(MAX_MASK << abs(yOset))) | board.board[x+xOset]<<abs(yOset);
                }
            }
        }
        for (uint8_t rot = PIECE_SYMMETRY[piece];rot<4;++rot) {
            for (int i=0;i<10;i++)this->map[rot][i]=this->map[rot%PIECE_SYMMETRY[piece]][i];
        }
    }

    bool CollisionMap::colliding(const uint8_t& x, const uint8_t& y, ROTATION rot, PIECE piece) {
        return this->map[rot][x]>>y&1;
    }

    bool CollisionMap::colliding(Piece &p) {
        return this->map[p.facing][p.x]>>p.y&1;
    }

    uint8_t CollisionMap::height(ROTATION rot,const uint8_t& x) {
        return uint8_t(32-countl_zero(this->map[rot][x]));
    }

    void CollisionMap::getHeightArray(ROTATION rot, uint8_t height[10]) {
        for (int i=0;i<10;i++) {
            height[i] = uint8_t(32-countl_zero(this->map[rot][i]));
        }
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
        memset(this->map, 0, sizeof this->map);
    }

    void PosMap::set(const int8_t x, const int8_t y, ROTATION r) {

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