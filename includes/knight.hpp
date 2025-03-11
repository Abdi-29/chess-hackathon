#pragma once

#include "piece.hpp"

class Knight : public Piece {
    public:
        Knight(bool color);
        std::vector<std::pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override;
};
    
