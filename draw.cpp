// //
// // Created by admin on 11/6/2024.
// //
//
// #include "board.h"
// #include "piece.h"
// #include "queue.h"
//
//
// sf::Color clrIdentify(string s) {
//     if (s == "#") return sf::Color::Black;
//     if (s == "Z") return {255,0,0};
//     if (s== "O") return {255,255,0};
//     if (s == "S") return {0, 255, 0};
//     if (s == "J") return {0,0,255};
//     if (s == "L") return {255, 165, 0};
//     if (s=="I") return {0, 255, 255};
//     if (s=="T") return {160, 32, 240};
//     return {0,0,0};
// }
//
// sf::Color clrIdentify(Cattris::PIECE p) {
//     string s = Cattris::piece_to_string(p);
//     return clrIdentify(s);
// }
//
// void Cattris::GameBoard::draw(sf::RenderWindow &window) {
//     sf::RectangleShape border(sf::Vector2f(320,620));
//     border.setPosition(140,170);
//     border.setFillColor(sf::Color::White);
//     window.draw(border);
//
//     for (int y = 19; y >= 0; y--) {
//         for (int x = 0; x < 10; x++) {
//             sf::RectangleShape block(sf::Vector2f(30,30));
//             block.setPosition(150 + x * 30, 150 + (20 - y) * 30);
//             block.setFillColor(clrIdentify(coloredBoard[y][x]));
//             window.draw(block);
//         }
//     }
// }
//
//
// void Queue::drawHold() {
//     if (hold.empty()) return;
//     //the left is 15, the right is 135
//     Cattris::Piece holdpiece = Piece(hold,board222,window);
//     holdpiece.dasleft();
//     if (holdpiece.piece != "I") holdpiece.right();
//     vector<Point> v = holdpiece.getCoords();
//
//     for (auto pr : v) {
//         sf::RectangleShape block(sf::Vector2f(30,30));
//         block.setPosition( 15 + (pr.x) * 30, 150 + (20 - pr.y) * 30);
//         block.setFillColor(clrIdentify(hold));
//         window.draw(block);
//     }
// }
//
// void Queue::drawQueue() {
//     //the left is 475, the right is 595
//     for (int i = 0; i < min(5,(int)upcoming.size()); i++) {
//         Piece queuepiece = Piece(upcoming[i],board222,window);
//         vector<Point> v = queuepiece.getCoords();
//         for (auto pr : v) {
//             sf::RectangleShape block(sf::Vector2f(30,30));
//             block.setPosition(400 + pr.x * 30,  (80 * i) + 150 + (20 - pr.y) * 30);
//             block.setFillColor(clrIdentify(upcoming[i]));
//             window.draw(block);
//         }
//     }
// }
//
// void Queue::draw() {
//     drawQueue();
//     drawHold();
// }
//
// void Piece::draw() {
//     //the left is 15, the right is 135
//     vector<Point> v = getCoords();
//     for (auto pr: v) {
//         sf::RectangleShape block(sf::Vector2f(30, 30));
//         block.setPosition(pr.x * 30 + 150, (20 - pr.y) * 30 + 150);
//         block.setFillColor(clrIdentify(piece));
//         window.draw(block);
//     }
// }
//
// void Piece::drawShadow() {
//     Piece shadow = *this;
//     shadow.sd();
//     vector<Point> coords = shadow.getCoords();
//     for (auto pr : coords) {
//         sf::RectangleShape block(sf::Vector2f(30,30));
//         block.setPosition(pr.x*30+150,(20-pr.y)*30+150);
//         block.setFillColor(sf::Color(122,122,122));
//         window.draw(block);
//     }
// }
//
// void drawAll(sf::
//
