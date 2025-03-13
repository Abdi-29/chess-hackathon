#pragma once

#include <string>
#include "piece.hpp"
#include <unordered_map>

using namespace std;

#define COL 8
#define ROW 8

class ChessBoard {
    private:
        unique_ptr<Piece> board[8][8];
        char active_color;
        pair<int, int> king_pos[2];
        unordered_map<string, vector<string>> opening_book;

    public:
        struct Move {
            int from_row, from_col;
            int to_row, to_col;
            std::unique_ptr<Piece> captured_piece;
            char promotion_piece = '\0';
            bool is_castling = false;
            bool is_en_passant = false;
        };

        ChessBoard();
        void parse_fen(const string& fen);
        void initialize_board();
        void update_king_position(int row, int col, bool is_white);
        void load_opening_book();
        string get_best_move_from_book(const string& fen);
        string get_best_move(int depth = 4, int movetime = -1);
        Move parse_move(const std::string& move_str);
        void make_move(const Move& move);
        string getFEN();
        vector<Move>& generate_legal_moves();
        void print_board();

        void uci_position(std::istringstream& iss, const string& fen);
        void uci_go(istringstream& iss);

};      
