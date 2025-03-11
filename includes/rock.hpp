#pragma once

#include "piece.hpp"

class Rook : public Piece {
    public:
        Rook(bool color);
        std::vector<std::pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override;
};
  
