#include "queue.h"
#include "board.h"
#include <random>
#include <chrono>
Queue::Queue(sf::RenderWindow &w): current(""),
                                   upcoming(),
                                   hold(),
                                   window(w),
                                   board222() {
    gen();
}

void Queue::gen() {
    mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    vector<string> bag = {"J","L","S","Z","I","O","T"};
    shuffle(bag.begin(),bag.end(),rng);
    for (auto x : bag) {
        upcoming.push_back(x);
    }
    if (!upcoming.empty()) {
        if (current.empty()) Pop();
    }
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
