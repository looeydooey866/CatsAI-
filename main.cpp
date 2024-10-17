#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "queue.h"
#include "board.h"

using namespace std;

void delay() {
    this_thread::sleep_for(chrono::milliseconds(8));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Tetris");
    Board board(window);
    Queue queue(window);
    window.setFramerateLimit(60);

    Piece now(queue.current, board, window);
    now.spawn();


    sf::Clock clock;
    bool isDasLeft = false;
    bool isDasRight = false;
    float dasThreshold = 90.0f;
    sf::Clock dasClock;

    bool spacePressed = false;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::White);
        queue.draw();
        queue.drawHold();
        board.draw();
        now.draw();
        window.display();
        // now.getEndPositions();
        vector<Piece> v;
        v.push_back(Piece("T",board,window));
        v.push_back(Piece("O",board,window));
        cout << "hi there" << endl;
        cout << v[0].piece << endl;
        v.pop_back();
        for (auto x:v) {
            cout << x.piece << "skibidi" << endl;
        }
        Piece curpiece = v[0];
        v.pop_back();
        curpiece.spawn();
        curpiece.sd();
        curpiece.placePiece();
        cout << curpiece.piece << "HIHAHE" << endl;
        cout << v.size() << endl;
        v.push_back(Piece("L",board,window));
        cout << "hi this is supposed to print an l!" << ' ' << (*v.begin()).piece << endl;
    }

    return 0;

}
