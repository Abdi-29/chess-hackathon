#pragma once

#include "piece.hpp"

class Pawn : public Piece {
    public:
        Pawn(bool white) : Piece(white, white ? 'P' : 'p') {}

        vector<pair<int, int>> get_moves(int row, int col, unique_ptr<Piece> board[8][8]) override {
            vector<pair<int, int>> moves;
            int direction = is_white ? 1 : -1;
            int start = is_white ? 1 : 6;
        
            if(row + direction >= 0 && row + direction < 8 && board[row + direction][col] == nullptr) {
                moves.push_back({row + direction, col});
            }
        
            if(row == start && board[row + 2 * direction][col] == nullptr) {
                moves.push_back({row + 2 * direction, col});
            }
        
            if(col > 0 && board[row + direction][col - 1] && board[row + direction][col - 1]->is_white != is_white) {
                moves.push_back({row + direction, col - 1});
            }

            if(col < 7 && board[row + direction][col + 1] && board[row + direction][col + 1]->is_white != is_white)
            {
                moves.push_back({row + direction, col + 1});
            }
        
            return moves;
        }
};
