#include "board.h"
#include "piece.h"

namespace Cattris {
    uint32_t &Board::operator [](int index) {
        assert(index > -1 && index < 10);
        return this->board[index];
    }

    bool Board::operator ==(const Board &other) {
        for (int i = 0; i < 10; i++) {
            if (this->board[i] != other.board[i]) return false;
        }
        return true;
    }

    void Board::set(const int8_t &x, const int8_t &y) {
        assert(y>=0&&y<25&&x>=0&&x<10);
        this->board[x] |= (static_cast<uint32_t>(1) << y);
    }


    bool Board::get(const int8_t &x, const int8_t &y) {
        return (this->board[x] >> y) & 1;
    }

    void Board::place(Piece &p) {
        for (uint8_t i = 0; i < 4; i++) {
            set(p.x + PIECE_COORDINATES[p.piece][p.facing][i][0], p.y + PIECE_COORDINATES[p.piece][p.facing][i][1]);
        }
    }

    void Board::place(int8_t &x, int8_t &y, PieceType piece, Rotation rot) {
        for (uint8_t i = 0; i < 4; i++) {
            set(x + PIECE_COORDINATES[piece][rot][i][0], y + PIECE_COORDINATES[piece][rot][i][1]);
        }
    }

    uint8_t Board::height(uint8_t x) {
        return 32 - countl_zero(this->board[x]);
    }

    void Board::getHeightArray(uint8_t height[10]) {
        for (uint8_t i = 0; i < 10; i++) {
            height[i] = 32 - countl_zero(this->board[i]);
        }
    }

    Tspin Board::isTspin(Piece &p) {
        if (p.piece != PieceType::T) {
            return Tspin::UNKNOWN;
        }
#define try(a,b) (a<0||a>=10||b<0||get(a,b))
        const uint8_t corners = try(p.x, p.y) + try(p.x+2, p.y) + try(p.x, p.y+2) + try(p.x+2, p.y+2);
        if (corners < 3) return Tspin::UNKNOWN;
        constexpr uint8_t xFac[5] = {0, 2, 2, 0, 0};
        constexpr uint8_t yFac[5] = {2, 2, 0, 0, 2};
        const uint8_t facing = get(p.x + xFac[p.facing], p.y + yFac[p.facing]) + get(
                                   p.x + xFac[p.facing + 1], p.y + yFac[p.facing + 1]);
        if (facing < 2) {
            return Tspin::MINI;
        }
        return Tspin::NORMAL;
    }

    Tspin Board::isTspin(const int8_t px, const int8_t py, const Rotation rotation, const PieceType piece) {
        if (piece != PieceType::T) {
            return Tspin::UNKNOWN;
        }
#define try(a,b) (a<0||a>=10||b<0||get(a,b))
        const uint8_t corners = try(px, py) + try(px+2, py) + try(px, py+2) + try(px+2, py+2);
        if (corners < 3) return Tspin::UNKNOWN;
        constexpr uint8_t xFac[5] = {0, 2, 2, 0, 0};
        constexpr uint8_t yFac[5] = {2, 2, 0, 0, 2};
        const uint8_t facing = get(px + xFac[rotation], py + yFac[rotation]) + get(
                                   px + xFac[rotation + 1], py + yFac[rotation + 1]);
        if (facing < 2) {
            return Tspin::MINI;
        }
        return Tspin::NORMAL;
    }

    uint32_t Board::getMask() {
        uint32_t mask = this->board[0];
        for (uint8_t i = 1; i < 10; i++) {
            mask &= this->board[i];
        }
        return mask;
    }

    uint8_t Board::fullLines() {
        return popcount(getMask());
    }

    void Board::clearLines() {
        uint32_t mask = getMask();
#ifdef X86
        mask = ~mask;
        for (uint8_t i=0;i<10;++i) {
            this->board[i] = _pext_u32(this->board[i], mask);
        }
#else
        if (mask == 0) {
            return;
        }
        const uint8_t height = countr_zero(mask);
        mask >>= height;
        for (uint8_t i = 0; i < 10; i++) {
            uint32_t lo = this->board[i] & ((1ULL << height) - 1ULL);
            uint32_t hi = this->board[i] >> height;
            if (mask == 0b0001) {
                hi >>= 1;
            } else if (mask == 0b0011) {
                hi >>= 2;
            } else if (mask == 0b0111) {
                hi >>= 3;
            } else if (mask == 0b1111) {
                hi >>= 4;
            } else if (mask == 0b0101) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 3) << 1);
            } else if (mask == 0b1001) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 2) << 1);
            } else if (mask == 0b1101) {
                hi = ((hi >> 1) & 0b0001) | ((hi >> 4) << 1);
            } else if (mask == 0b1011) {
                hi = ((hi >> 2) & 0b0001) | ((hi >> 4) << 1);
            }

            this->board[i] = lo | (hi << height);
        }
#endif
    }

    void Board::print() {
        string ret;
        for (int i = 0; i < 10; i++) {
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
            for (int j = 0; j < 10; j++) {
                ret += "---";
                ret += "+";
            }
            ret += "\n";
        }
        cout << ret << "\n";
    }

    void Board::setfill(const int8_t &x1, const int8_t &y1, const int8_t &x2, const int8_t &y2) {
        assert(y1>=0&&y1<25&y2>=0&&y2<25&&x1>=0&&x1<10&&x2>=0&&x2<10);
        for (int8_t x = min(x1, x2); x <= max(x1, x2); x++) {
            for (int8_t y = min(y1, y2); y <= max(y1, y2); y++) {
                this->set(x, y);
            }
        }
    }

    void Board::setstring(const string s, int y) {
        assert(s.size()==10 && y >= 0 && y < 25);
        for (int i = 0; i < 10; i++) {
            if (s[i] == '1') set(i, y);
        }
    }

    void Board::setBigString(const string s, int y) {
        assert(s.size()%10==0 && y >= 0 && y + (s.size()/10) - 1 < 25);
        for (uint8_t i = 0; i < s.size() / 10; i++) {
            this->setstring(s.substr(i * 10, 10), (s.size() / 10 - i - 1) + y);
        }
    }

    void printbin(uint32_t x) {
        uint32_t msb = UINT32_MAX ^ (UINT32_MAX >> 1);
        string ret;
        ret += "0b";
        while (msb) {
            ret += (x&msb?"1":"0");
            msb>>=1;
        }
        cout << ret << "\n";
    }

    void fancyprint(uint32_t x) {
        uint32_t msb = UINT32_MAX ^ (UINT32_MAX >> 1);
        string ret;
        while (msb) {
            if (31-int(countl_zero(msb))<10) ret+=" ";
            ret += std::to_string(int(31 - int(countl_zero(msb))));
            ret += "|";
            ret += (x&msb?"[]":"  ");
            ret+="|";
            ret+="\n";
            msb>>=1;
        }
        cout << ret << "\n";
    }

    void fancyprint(uint32_t x[10]) {
        uint32_t msb = UINT32_MAX ^ (UINT32_MAX >> 1);
        string ret;
        while (msb) {
            if (31-int(countl_zero(msb))<10) ret+=" ";
            ret += std::to_string(int(31-int(countl_zero(msb))));
            ret += "|";
            for (int i=0;i<10;++i) {
                ret += (x[i]&msb?"[]":"  ");
            }
            ret += "|";
            ret+="\n";
            msb>>=1;
        }
        cout << ret << "\n";
    }

    void fancyprint(uint32_t x[10], uint32_t y[10]) {
        uint32_t msb = UINT32_MAX ^ (UINT32_MAX >> 1);
        string ret;
        while (msb) {
            if (31-int(countl_zero(msb))<10) ret+=" ";
            ret += std::to_string(int(31-int(countl_zero(msb))));
            ret += "|";
            for (int i=0;i<10;++i) {
                ret += (x[i]&msb?"[]":
                    (y[i]&msb?"{}":"  "));
            }
            ret += "|";
            ret+="\n";
            msb>>=1;
        }
        cout << ret << "\n";
    }
}
