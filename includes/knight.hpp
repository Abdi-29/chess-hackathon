#pragma once

#include "piece.hpp"

class Knight : public Piece {
    public:
        Knight(bool white) : Piece(white, white ? 'N' : 'n') {}

        vector<pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override {
            vector<pair<int, int>> moves;
            static const int offsets[8][2] = {
                {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
            };
        
            for(auto [dr, dc] : offsets) {
                int nr = row + dr, nc = col + dc;
                if(nr >= 0 && nr < 8 && nc >= 0 && nc < 8 && 
                    (board[nr][nc] == nullptr || board[nr][nc]->is_white != is_white)) {
                    moves.push_back({nr, nc});
                }
            }
            return moves;
        }
};
    
