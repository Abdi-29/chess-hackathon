#pragma once

#include <string>
#include "piece.hpp"
#include <unordered_map>

using namespace std;

#define COL 8
#define ROW 8

class ChessBoard {
    private:
        Piece* board[8][8] = {};
        char active_color;
        pair<int, int> king_pos[2];
        unordered_map<string, vector<string>> opening_book;

    public:
        ChessBoard();
        void parse_fen(const string& fen);
        void initialize_board();
        void update_king_position(int row, int col, bool is_white);
        void load_opening_book();
        string get_book_move();
        void print_board();
};      
