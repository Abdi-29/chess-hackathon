#pragma once

#include "piece.hpp"

class King : public Piece {
    public:
        King(bool white);
        std::vector<std::pair<int, int>> get_movess(int row, int col, Piece* board[8][8]) override;
};    
      
