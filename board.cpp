//
// Created by admin on 10/9/2024.
//
#include <bits/stdc++.h>
using namespace std;
#include <SFML/graphics.hpp>
#include "board.h"

sf::Color clrIdentify(string s) {
    if (s == "#") return sf::Color::Black;
    if (s == "Z") return {255,0,0};
    if (s== "O") return {255,255,0};
    if (s == "S") return {0, 255, 0};
    if (s == "J") return {0,0,255};
    if (s == "L") return {255, 165, 0};
    if (s=="I") return {0, 255, 255};
    if (s=="T") return {160, 32, 240};
    return {128, 128, 128};
}

void Board::draw() {
    for (int y = 19; y >= 0; y--) {
        for (int x = 0; x < 10; x++) {
            sf::RectangleShape block(sf::Vector2f(30,30));
            block.setPosition(150 + x * 30, 150 + (20 - y) * 30);
            block.setFillColor(clrIdentify(coloredBoard[y][x]));
            window.draw(block);
        }
    }
}

void Board::clearLines() {
    Board newboard = Board(window);
    int ctr=0;
    for (int y=0; y<21; y++) {
        bool fullLine = false;
        if ((~bitBoard & ((bitset<250>("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111"))<<(10*y))).none()) {
            fullLine = true;
        }
        if (!fullLine) {
            bitset<250> row = bitBoard & ((bitset<250>("0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111111111"))<<(10*y));
            row >>= y*10;
            row <<= ctr*10;
            newboard.bitBoard |= row;
            for (int x=0;x<10;x++) {
                newboard.coloredBoard[ctr][x] = coloredBoard[y][x];
            }
            ctr++;
        }
    }
    bitBoard = newboard.bitBoard;
    coloredBoard = newboard.coloredBoard;
}

