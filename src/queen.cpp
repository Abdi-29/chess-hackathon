#include "../includes/queen.hpp"

Queen::Queen(bool white) : Piece(white, white ? 'Q' : 'q') {}

vector<pair<int, int>> get_moves(int row, int col, Piece* board[8][8]) override {
    vector<pair<int, int>> moves;
    int directions[8][2] = {
        {1, 1}, {1, -1}, {-1, 1}, {-1, -1},
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    };

    for(auto [dr, dc] : directions) {
        for(int d = 1; d < ROW; d++) {
            int nr = row + dr * d, nc = col + dc * d;
            if(nr < 0 || nr >= ROW || nc < 0 || nc >= ROW) {
                break;
            } 
            if(board[nr][nc] == nullptr) {
                moves.push_back({nr, nc});
            } else {
                if (board[nr][nc]->is_white != is_white) {
                    moves.push_back({nr, nc});
                }
                break;
            }
        }
    }
    return moves;
}