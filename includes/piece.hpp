#pragma once

#include <iostream>
#include <vector>
// #include <memory>

using namespace std;
class Piece {
    public:
        bool is_white;
        char type;
        Piece(bool color, char t);
        virtual vector<pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) = 0;
        virtual ~Piece() = default;
};

