#include "queue.h"
#include "board.h"

Queue::Queue(sf::RenderWindow &w): current(),
                                   upcoming(),
                                   hold(),
                                   window(w),
                                   board222(w) {
    gen();
}

void Queue::gen() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    vector<string> bag = {"J","L","S","Z","I","O","T"};
    shuffle(bag.begin(),bag.end(),rng);
    for (auto x : bag) {
        upcoming.push_back(x);
    }
    if (current.empty()) Pop();
}

void Queue::drawHold() {
    if (hold.empty()) return;
    //the left is 15, the right is 135
    Piece holdpiece = Piece(hold,board222,window);
    vector<Point> v = holdpiece.getCoords();

    for (auto pr : v) {
        sf::RectangleShape block(sf::Vector2f(30,30));
        block.setPosition(15 + pr.x * 30, -325 + (20 - pr.y) * 30);
        block.setFillColor(clrIdentify(hold));
        window.draw(block);
    }
}

void Queue::drawQueue() {
    //the left is 475, the right is 595
    for (int i = 0; i < 5; i++) {
        Piece queuepiece = Piece(upcoming[i],board222,window);
        vector<Point> v = queuepiece.getCoords();
        for (auto pr : v) {
            sf::RectangleShape block(sf::Vector2f(30,30));
            block.setPosition(500 + pr.x * 30,  (80 * i) + -325 + (20 - pr.y) * 30);
            block.setFillColor(clrIdentify(upcoming[i]));
            window.draw(block);
        }
    }
}

void Queue::draw() {
    drawQueue();
    drawHold();
}

void Queue::holdPiece() {
    if (hold.empty()) {
        hold = current;
        Pop();
    }
    else {
        string holder = hold;
        hold = current;
        current = holder;
    }
}

void Queue::Pop() {
    current = upcoming[0];
    upcoming.pop_front();
}
