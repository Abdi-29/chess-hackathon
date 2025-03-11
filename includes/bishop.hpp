#pragma once

#include "piece.hpp"

class Bishop : public Piece {
    public:
        Bishop(bool white);
        vector<pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override;
};
