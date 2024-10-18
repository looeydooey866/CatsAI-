#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "queue.h"
#include "board.h"
#include "myheap.h"

using namespace std;

int64_t DELAYTIME = 8;
void delay() {
    this_thread::sleep_for(chrono::milliseconds(DELAYTIME));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Tetris");
    Board board(window);
    Queue queue(window);
    window.setFramerateLimit(60);

    Piece now(queue.current, board, window);
    now.spawn();

    while (window.isOpen()) {
        //game loop
        queue.Pop();
        if (queue.upcoming.size() < 8) queue.gen();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        //i should make this a function hmmmmmmmmmmmmmmmm
        window.clear(sf::Color::White);
        queue.draw();
        queue.drawHold();
        board.draw();
        now.draw();
        window.display();
        // now.getEndPositions(); WORK IN PROGRESS
    }
}
