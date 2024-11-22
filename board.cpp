//
// Created by admin on 10/9/2024.
//
#include "board.h"
#include "piece.h"

namespace Cattris {
    ui32& Board::operator [] (int index) {
        assert(index > -1 && index < 10);
        return this->board[index];
    }

    bool Board::operator == (const Board& other) {
        for (int i=0;i<10;i++) {
            if (this->board[i] != other.board[i]) return false;
        }
        return true;
    }

    void Board::set(const i8& x, const i8 &y) {
        assert(y>=0&&y<25&&x>=0&&x<10);
        this->board[x] |= (static_cast<ui32>(1) << y);
    }

    void Board::setfill(const i8 &x1, const i8 &y1, const i8 &x2, const i8 &y2) {
        assert(y1>=0&&y1<25&y2>=0&&y2<25&&x1>=0&&x1<10&&x2>=0&&x2<10);
        for (i8 x=min(x1,x2);x<=max(x1,x2);x++) {
            for (i8 y=min(y1,y2);y<=max(y1,y2);y++) {
                this->set(x,y);
            }
        }
    }

    void Board::setstring(const string s, int y) {
        assert(s.size()==10 && y >= 0 && y < 25);
        for (int i=0;i<10;i++) {
            if (s[i]=='1') set(i,y);
        }
    }

    void Board::setBigString(const string s, int y) {
        assert(s.size()%10==0 && y >= 0 && y + (s.size()/10) - 1 < 25);
        for (ui8 i=0;i<s.size()/10;i++){
            this->setstring(s.substr(i*10,10),(s.size()/10-i-1)+y);
        }
    }

    void Board::place(Piece &p) {
        for (ui8 i=0;i<4;i++) {
            set(p.x+PIECE_COORDINATES[p.piece][p.facing][i][0],p.y+PIECE_COORDINATES[p.piece][p.facing][i][1]);
        }
    }

    void Board::place(i8 &x, i8 &y, PIECE piece, ROTATION rot) {
        for (ui8 i=0;i<4;i++) {
            set(x+PIECE_COORDINATES[piece][rot][i][0],y+PIECE_COORDINATES[piece][rot][i][1]);
        }
    }


    bool Board::get(const i8 &x, const i8 &y) {
        return (this->board[x] >> y) & static_cast<ui32>(1);
    }

    ui8 Board::height(ui8 x) {
        return 32 - countl_zero(this->board[x]);
    }

    void Board::getHeightArray(ui8 height[10]) {
        for (ui8 i=0;i<10;i++) {
            height[i] = 32 - countl_zero(this->board[i]);
        }
    }

    TSPIN Board::isTspin(Piece &p) {
        if (p.piece != PIECE::T) {
            return TSPIN::UNKNOWN;
        }
        ui8 corners = 0;
        ui8 x = p.x;
        ui8 y = p.y;
#define try(a,b) if (a<0||a>=10||b<0||get(a,b)) corners++;
        try(x,y);
        try(x+2,y);
        try(x,y+2);
        try(x+2,y+2);
        if (corners < 3) return TSPIN::UNKNOWN;
        constexpr ui8 xFac[5] = {0,2,2,0,0};
        constexpr ui8 yFac[5] = {2,2,0,0,2};
        ui8 facing = get(x+xFac[p.facing],y+yFac[p.facing]) + get(x+xFac[p.facing+1],y+yFac[p.facing+1]);
        if (facing < 2) {
            return TSPIN::MINI;
        }
        return TSPIN::NORMAL;
    }

    TSPIN Board::isTspin(const i8 px, i8 py, ROTATION rotation, PIECE piece) {
        if (piece != PIECE::T) {
            return TSPIN::UNKNOWN;
        }
        ui8 corners = 0;
#define try(a,b) if (a<0||a>=10||b<0||get(a,b)) corners++;
        try(px,py);
        try(px+2,py);
        try(px,py+2);
        try(px+2,py+2);
        if (corners < 3) return TSPIN::UNKNOWN;
        constexpr ui8 xFac[5] = {0,2,2,0,0};
        constexpr ui8 yFac[5] = {2,2,0,0,2};
        ui8 facing = get(px+xFac[rotation],py+yFac[rotation]) + get(px+xFac[rotation+1],py+yFac[rotation+1]);
        if (facing < 2) {
            return TSPIN::MINI;
        }
        return TSPIN::NORMAL;
    }

    ui32 Board::getMask() {
        ui32 mask = this->board[0];
        for (ui8 i=1;i<10;i++) {
            mask &= this -> board[i];
        }
        return mask;
    }

    ui8 Board::fullLines() {
        return popcount(getMask());
    }

    void Board::clearLines() {
        ui32 mask = getMask();
#ifdef X86
        mask = ~mask;
        for (ui8 i=0;i<10;++i) {
            this->board[i] = _pext_u32(this->board[i], mask);
        }
#else
        if (mask==0) {
            return;
        }
        const ui8 height = countr_zero(mask);
        mask >>= height;
        for (ui8 i=0;i<10;i++) {
            ui32 lo = this->board[i] & ((1ULL << height) - 1ULL);
            ui32 hi = this->board[i] >> height;
            if (mask == 0b0001) {
                hi >>= 1;
            }
            else if (mask == 0b0011) {
                hi >>= 2;
            }
            else if (mask == 0b0111) {
                hi >>= 3;
            }
            else if (mask == 0b1111) {
                hi >>= 4;
            }
            else if (mask == 0b0101) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 3) << 1);
            }
            else if (mask == 0b1001) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 2) << 1);
            }
            else if (mask == 0b1101) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 4) << 1);
            }
            else if (mask == 0b1011) {
                hi = ((hi >> 2) & 0b0001) | ((hi >> 4) << 1);
            }

            this->board[i] = lo | (hi << height);
        }
#endif
    }

    void Board::print() {
        string ret;
        for (int i=0;i<10;i++) {
            ret += "+";
            ret += "---";
        }
        ret += "+\n";
        for (int i = 24; i >= 0; i--) {
            ret += "| ";
            for (int j = 0; j < 10; j++) {
                ret += (this->board[j] >> i & 1 ? "#" : ".");
                if (9 - j) ret += " | ";
            }
            ret += " |";
            ret += "\n";
            ret += "+";
            for (int j=0;j<10;j++) {
                ret += "---";
                ret += "+";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }

    void CollisionMap::populate(Board &board, PIECE piece) {
        memset(this->map,0,sizeof(this->map));
        ui32 MAX_MASK = ~ui32(0);
        for (ui8 rot = 0; rot < PIECE_SYMMETRY[piece]; ++rot) {
            for (ui8 mino = 0; mino < 4; ++mino) {
                i8 xOset = CENTER_OSETS[piece][rot][mino][0];
                i8 yOset = CENTER_OSETS[piece][rot][mino][1];
                for (ui8 x = 0; x < 10; ++x) {
                    this->map[rot][x] |= ( (x+xOset >= 10) ? MAX_MASK : ( (yOset >= 0) ? board.board[x + xOset] >> yOset : ((1ULL << abs(yOset)) - 1) | board.board[x + xOset] << abs(yOset) ) );
                }
            }
        }
        for (ui8 rot = PIECE_SYMMETRY[piece]; rot < 4; ++rot) {
            memcpy(this->map[rot],this->map[rot%PIECE_SYMMETRY[piece]],sizeof(this->map[0]));
        }
    }

    bool CollisionMap::colliding(i8 x,i8 y, ROTATION rot, PIECE piece) const{
#define pc PIECE_COORDINATES
        x += pc[piece][rot][0][0];
        y += pc[piece][rot][0][1];
        return (x < 0 || x >= 10 || y < 0) || (((this->map[rot][x]>>y)&1));
#undef pc
    }

    bool CollisionMap::colliding(Piece &p) const{
        return this->map[p.facing][p.x+PIECE_COORDINATES[p.piece][p.facing][0][0]]>>(p.y+PIECE_COORDINATES[p.piece][p.facing][0][1])&1;
    }

    ui8 CollisionMap::height(ROTATION rot,ui8 x, PIECE piece) {
        return ui8(32-countl_zero(this->map[rot][x + PIECE_COORDINATES[piece][rot][0][0]]));
    }

    void CollisionMap::getHeightArray(ROTATION rot, ui8 height[10], PIECE piece) {
        for (ui8 i=0;i<10;i++) {
            height[i] = ui8(32-countl_zero(this->map[rot][i]));
        }
    }

    void CollisionMap::print(int rot) {
        string ret;
        for (int i=0;i<10;i++) {
            ret += "+";
            ret += "---";
        }
        ret += "+\n";
        for (int i = 24; i >= 0; i--) {
            ret += "| ";
            for (int j = 0; j < 10; j++) {
                ret += (this->map[rot][j] >> i & 1 ? "#" : ".");
                if (9 - j) ret += " | ";
            }
            ret += " |";
            ret += "\n";
            ret += "+";
            for (int j=0;j<10;j++) {
                ret += "---";
                ret += "+";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }

    void GameBoard::clear() {
        memset(this->coloredBoard,'.',sizeof this->coloredBoard);
    }

    void GameBoard::clearLines() {
        string ret;
        for (ui8 y=0;y<25;y++) {
            bool ok=true;
            for (ui8 x=0;x<10;x++) {
                if (this->coloredBoard[y][x]!='.') ok=false;
            }
            if (!ok) continue;

            ret = ret + this->coloredBoard[y];
        }
        for (ui8 y=0;y<ret.size()/10;y++) {
            this->coloredBoard[y] = ret.substr(y*10,10);
        }
    }

    void GameBoard::set(int x, int y, char type) {
        this->coloredBoard[y][x]=type;
    }
}