#pragma once

#include <string>
#include "piece.hpp"
// #include "move.hpp"
// #include "pawn.hpp"
// #include "knight.hpp"
// #include "rock.hpp"
// #include "king.hpp"
// #include "bishop.hpp"
// #include "queen.hpp"

using namespace std;

#define COL 8
#define ROW 8

class ChessBoard {
    private:
        Piece* board[8][8] = {};
        char active_color;

        // vector<Move> generate_king_move(int row, int col, char color) const;
        // vector<Move> generate_queen_move(int row, int col, char color) const;
        // vector<Move> generate_rock_move(int row, int col, char color) const;
        // vector<Move> generate_knight_move(int row, int col, char color) const;
        // vector<Move> generate_bishop_move(int row, int col, char color) const;

    public:
        ChessBoard();
        void parse_fen(const string& fen);
        // vector<Move> generate_move(char color) const;
        // void fill_board(const string& rank, int row);
        void print_board();  
};      
