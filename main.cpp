#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include "piece.h"
#include "queue.h"
#include "board.h"

using namespace std;

int main() {
    Cattris::Board board;
    // board.set(4,6);
    board[4] = 64;
    board[7] = 16;
    Cattris::CollisionMap colmap{};
    int tot = 0;
    auto now = chrono::high_resolution_clock::now();
    do {
        colmap.populate(board, Cattris::PIECE::L);
        ++tot;
    } while (duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - now).count() < 10000);

    string out;
    out += format("I did {:d} runs on average.", tot/10);
    cout << out << endl;
    board.print();
    for (int i=0;i<4;i++) {
        colmap.print(i);
    }
}

/*int main() {
    sf::RenderWindow window(sf::VideoMode(1200,1200),"Tetrizz");
    Board board(window);
    Queue queue(window);
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type==sf::Event::Closed) {
                window.close();
            }
        }
        Piece cur(queue.current, board, window);
        cur.spawn();
        auto start = chrono::steady_clock::now();
        vector<Piece> x = cur.getEndPositions();
        auto end = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - start);
        cout << fixed << setprecision(10);
        cout << "Finding all of the end positions of the piece took me a grand total of: " << endl;
        cout << elapsed << " NANOseconds!" << endl;
        auto paths = cur.getEndPaths();
        queue.Pop();
        queue.gen();
        for (auto piece: x) {

            Board copy = board;
            Piece curcopy = Piece(piece.piece,copy,window);
            curcopy.spawn();
            for (auto path : paths) {
                if (path.second.coords.x==piece.coords.x&&path.second.coords.y==piece.coords.y&&path.second.rotations==piece.rotations) {
                    for (auto move : path.first) {
                        window.clear(sf::Color::White);
                        curcopy.stringToMove(move);
                        copy.draw();
                        curcopy.draw();
                        queue.draw();
                        window.display();
                        this_thread::sleep_for(std::chrono::milliseconds(200));
                    }
                }
            }

        }
    }

}*/

//you control
/*
int main() {
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "Tetris");
    Board board(window);
    Queue queue(window);
    window.setFramerateLimit(60);

    Piece now(queue.current, board, window);
    now.spawn();


    sf::Clock clock;
    bool isDasLeft = false;
    bool isDasRight = false;
    bool sdHeld = false;
    float dasThreshold = 90.0f;
    sf::Clock dasClock;

    bool spacePressed = false;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        isDasRight = false;
                        if (!isDasLeft) {
                            now.left();
                            isDasLeft = true;
                            dasClock.restart();
                        }

                        break;

                    case sf::Keyboard::Right:
                        isDasLeft = false;
                        if (!isDasRight) {
                            now.right();
                            isDasRight = true;
                            dasClock.restart();
                        }

                        break;

                    case sf::Keyboard::Up:
                        now.cw();
                        break;
                    case sf::Keyboard::Down:
                        now.sd();
                        sdHeld = true;
                        break;
                    case sf::Keyboard::A:
                        now.ccw();
                        now.ccw();
                        break;
                    case sf::Keyboard::S:
                        now.ccw();
                        break;
                    case sf::Keyboard::D:
                        queue.holdPiece();
                        now.piece = queue.current;
                        now.updateBitset();
                        now.spawn();
                        now.spawn();
                        now.coords.x = now.getOset();
                        break;
                    case sf::Keyboard::Space:
                        if (!spacePressed) {
                            now.sd();
                            now.placePiece();
                            board.clearLines();
                            queue.Pop();
                            queue.gen();
                            now.piece = queue.current;
                            now.updateBitset();
                            now.spawn();
                            spacePressed = true;
                            delay();
                        }
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }


            if (event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                    case sf::Keyboard::Left:
                        isDasLeft = false;
                        break;
                    case sf::Keyboard::Right:
                        isDasRight = false;
                        break;
                    case sf::Keyboard::Space:
                        spacePressed = false;
                        break;
                    case sf::Keyboard::Down:
                        sdHeld = false;
                        break;
                    default:
                        break;
                }
            }
        }


        if (isDasLeft) {
            if (dasClock.getElapsedTime().asMilliseconds() >= dasThreshold) {
                now.dasleft();
            }
        }


        if (isDasRight) {
            if (dasClock.getElapsedTime().asMilliseconds() >= dasThreshold) {
                now.dasright();
            }
        }

        if (sdHeld) {
            now.sd();
        }


        window.clear(sf::Color::Black);
        queue.draw();
        queue.drawHold();
        board.draw();
        //draw the shadow first LOL
        now.drawShadow();
        now.draw();
        window.display();
        // now.getEndPositions();
    }

    return 0;

}
*/