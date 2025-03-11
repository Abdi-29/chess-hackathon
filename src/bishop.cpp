#include "../includes/bishop.hpp"

Bishop::Bishop(bool white) : Piece(white, white ? 'B' : 'b') {}

vector<pair<int, int>> Bishop::get_moves(int row, int col, Piece* board[8][8]) override {
    vector<pair<int, int>> moves;
    int directions[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

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