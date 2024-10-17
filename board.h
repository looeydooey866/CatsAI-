// Board.h
#ifndef BOARD_H
#define BOARD_H

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
using namespace std;
sf::Color clrIdentify(string s);

struct Board {
    sf::RenderWindow& window;
    vector<vector<string>> coloredBoard = vector<vector<string>>(25,vector<string>(10,"#"));
    bitset<250> bitBoard;
    explicit Board(sf::RenderWindow& w) : window(w) {}

    void draw();

    void clearLines();
};

#endif
