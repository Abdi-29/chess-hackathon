#pragma once

#include "piece.hpp"

class Queen : public Piece {
    public:
        Queen(bool white);
        std::vector<std::pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override;
};
