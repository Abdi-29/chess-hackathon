#include "chessboard.hpp"
#include <sstream>
#include <fstream>
#include <cctype>
#include "pawn.hpp"
#include "knight.hpp"
#include "rock.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "piece.hpp"
#include <random>

ChessBoard::ChessBoard() {
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            board[i][j] = nullptr;
        }
    }
    active_color = 'w';
    initialize_board();
}

void ChessBoard::parse_fen(const string& fen) {
    istringstream iss(fen);
    string pieces;
    iss >> pieces >> active_color;

    cout << "pieces: " << pieces << endl;
    cout << "color: " << active_color << endl;

    int row = ROW - 1;
    int col = 0;

    for(char c: pieces) {
        if(c == '/') {
            row--;
            col = 0;
        } else if(isdigit(c)) {
            col += c - '0';
        } else {
            bool is_white = isupper(c);
            switch (tolower(c)) {
                case 'r': board[row][col] = new Rock(is_white); break;
                case 'n': board[row][col] = new Knight(is_white); break;
                case 'p': board[row][col] = new Pawn(is_white); break;
                case 'k': board[row][col] = new King(is_white); break;
                case 'q': board[row][col] = new Queen(is_white); break;
                case 'b': board[row][col] = new Bishop(is_white); break;   
            }
            col++;
        }
    }
}

void ChessBoard::initialize_board() {
    king_pos[0] = {7, 4};
    king_pos[1] = {0, 4};
}

void ChessBoard::update_king_position(int row, int col, bool is_white) {
    king_pos[is_white ? 0 : 1] = {row, col};
}

void ChessBoard::load_opening_book() {
    ifstream file("opening_book.txt");
    string fen, moves_line;
    while (getline(file, fen)) {
        if (getline(file, moves_line)) {
            istringstream iss(moves_line);
            string move;
            vector<string> moves;
            while (iss >> move) {
                moves.push_back(move);
            }
            opening_book.emplace(fen, std::move(moves));
        }
    }
}

string ChessBoard::get_book_move() {
    
}

void ChessBoard::print_board() {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            if(board[i][j] != nullptr) {
                cout << board[i][j]->type;
            } else {
                cout << ".";
            }
        }
        cout << endl;
    }
}