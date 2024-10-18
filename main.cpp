#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "piece.h"
#include "queue.h"
#include "board.h"
#include "myheap.h"

using namespace std;

int64_t DELAYTIME = 1;

void delay() {
    this_thread::sleep_for(chrono::milliseconds(DELAYTIME));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(900, 1000), "Tetris");
    Board board(window);
    Queue queue(window);
    window.setFramerateLimit(60);
    int ctr = 1;

    Piece now(queue.current, board, window);
    now.spawn();
    Piece moves("L",board,window);
    moves.rotations = 1;
    moves.updateBitset();
    moves.coords.x=-1;
    moves.sd();
    moves.placePiece();
    moves.piece = "I";
    moves.spawn();
    moves.sd();
    moves.placePiece();
    moves.piece="Z";
    moves.spawn();
    moves.sd();
    moves.placePiece();
    moves.piece="J";
    moves.spawn();
    moves.cw();
    moves.cw();
    moves.sd();
    moves.placePiece();
    moves.piece="S";
    moves.spawn();
    moves.cw();
    moves.right();
    moves.right();
    moves.sd();
    moves.placePiece();
    moves.piece="O";
    moves.spawn();
    moves.dasright();
    moves.sd();
    moves.placePiece();
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
        now.piece="T";
        now.updateBitset();
        auto positions = now.getEndPositions();
       //  for (int i=0;i<positions.size();i++) {
       //      for (int j=0;j<positions.size()-1;j++) {
       //          if (positions[j].second.coords.x*4-positions[j].second.getLeftSpace()>positions[j+1].second.coords.x*4-positions[j+1].second.getLeftSpace()) {
       //              swap(positions[j].first,positions[j+1].first);
       //              swapPiece(positions[j].second,positions[j+1].second);
       //          }
       //      }
       //  }
       // for (int i=0;i<4;i++) {
       //     for (auto position: positions) {
       //      Piece cur = position.second;
       //      if (cur.rotations==i) {
       //          string tspin = cur.tSpinCheck();
       //          cout << tspin << endl;
       //          cur.spawn();
       //          for (string move: position.first) {
       //              cur.stringToMove(move);
       //              window.clear(sf::Color::White);
       //              queue.draw();
       //              queue.drawHold();
       //              board.draw();
       //              cur.draw();
       //              window.display();
       //              delay();
       //          }
       //      }
       //  }
           window.clear(sf::Color::White);
           queue.draw();
           queue.drawHold();
           board.draw();

           window.display();
        queue.Pop();
    }
}
