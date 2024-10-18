//
// Created by admin on 10/17/2024.
//

#ifndef MYHEAP_H
#define MYHEAP_H
#include "piece.h"
#include <bits/stdc++.h>
using namespace std;

struct MyHeap {
    vector<pair<Piece,int>> pieces;

    pair<Piece,int> top() {
        return pieces[0];
    }

    void insert(Piece x, int dist) {
        int i = pieces.size();
        pieces.emplace_back(x, dist);
        while (i != 0) {
            if (pieces[i].second < pieces[(i-1)/2].second) {
                swap(pieces[i].second,pieces[(i-1)/2].second);
                swapPiece(pieces[i].first,pieces[(i-1)/2].first);
                i = (i-1)/2;
            }
            else {
                break;
            }
        }
    }
    void pop() {
        swap(pieces[0].second,pieces[pieces.size()-1].second);
        swapPiece(pieces[0].first,pieces[pieces.size()-1].first);
        pieces.pop_back();
        int i = 0;
        while (2*i+1 < pieces.size() && pieces[i].second > min(pieces[2*i+1].second,(2*i+2<pieces.size()?pieces[2*i+2].second:INT_MAX))) {
            if (pieces[2*i+1].second <= (2*i+2<pieces.size()?pieces[2*i+2].second:INT_MAX)) {
                swap(pieces[i].second,pieces[2*i+1].second);
                swapPiece(pieces[i].first,pieces[2*i+1].first);
                i = 2 * i + 1;
            }
            else {
                swap(pieces[i].second, pieces[2*i+2].second);
                swapPiece(pieces[i].first,pieces[2*i+2].first);
                i = 2 * i + 2;
            }
        }
    }
};
#endif //MYHEAP_H
