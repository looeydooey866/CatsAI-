//
// Created by admin on 10/10/2024.
//
#pragma once
#include "board.h"
#include "piece.h"
#ifndef QUEUE_H
#define QUEUE_H

//
// Created by admin on 10/10/2024.
//


struct Queue {

    string current;
    deque<string> upcoming;
    string hold;
    sf::RenderWindow& window;
    Cattris::Board board222;

    explicit Queue(sf::RenderWindow& w);

    void gen();

    void drawHold();

    void drawQueue();

    void draw();

    void holdPiece();

    void Pop();
};

#endif //QUEUE_H
