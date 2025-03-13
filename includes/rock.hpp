#pragma once

#include "piece.hpp"

class Rock : public Piece {
    public:
        Rock(bool white) : Piece(white, white ? 'R' : 'r') {}

        vector<pair<int, int>> get_moves(int row, int col, unique_ptr<Piece> board[8][8]) override {
            vector<pair<int, int>> moves;
            const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
            for(auto [dr, dc] : directions) {
                for(int d = 1; d < 8; d++) {
                    int nr = row + dr * d, nc = col + dc * d;
                    if(nr < 0 || nr >= 8 || nc < 0 || nc >= 8) {
                        break;
                    } else if(board[nr][nc] == nullptr) {
                        moves.push_back({nr, nc});
                    } else {
                        if(board[nr][nc]->is_white != is_white) {
                            moves.push_back({nr, nc});
                        }
                        break;
                    }
                }
            }
            return moves;
        }
};
  
