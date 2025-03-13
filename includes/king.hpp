#pragma once

#include "piece.hpp"

class King : public Piece {
    public:
        King(bool white) : Piece(white, white ? 'K' : 'k') {}

        vector<pair<int, int>> get_moves(int row, int col, unique_ptr<Piece> board[8][8]) override {
            vector<pair<int, int>> moves;
            const int directions[8][2] = {
                {1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}
            };
        
            for(auto [dr, dc] : directions) {
                int nr = row + dr;
                int nc = col + dc;
                if(nr >= 0 && nr < 8 && nc >= 0 && nc < 8 &&
                    (board[nr][nc] == nullptr || board[nr][nc]->is_white != is_white)) {
                    moves.push_back({nr, nc});
                }
            }
            return moves;
        }
};