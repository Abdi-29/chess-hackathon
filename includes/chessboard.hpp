#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP

#include <string>
#include <iostream>
#include <vector>
#include "move.hpp"

using namespace std;

#define COL 8
#define ROW 8

class ChessBoard {
    private:
        char _board[8][8];
        char _active_color;

        vector<Move> generate_king_move(int row, int col, char color) const;
        vector<Move> generate_queen_move(int row, int col, char color) const;
        vector<Move> generate_rock_move(int row, int col, char color) const;
        vector<Move> generate_knight_move(int row, int col, char color) const;
        vector<Move> generate_bishop_move(int row, int col, char color) const;

    public:
        ChessBoard();
        void parse_fen(const string& fen);
        vector<Move> generate_move(char color) const;
        void fill_board(const string& rank, int row);
        void print_board();  
};      

#endif