#include "chessboard.hpp"
#include <sstream>
#include <cctype>
#include "pawn.hpp"
#include "knight.hpp"
#include "rock.hpp"
#include "king.hpp"
#include "bishop.hpp"
#include "queen.hpp"
#include "piece.hpp"

ChessBoard::ChessBoard() {
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            board[i][j] = nullptr;
        }
    }
    active_color = 'w';
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

    // print_board();
}

// void ChessBoard::fill_board(const string& rank, int row) {
//     int col = 0;

//     for(char c: rank) {
//         if(isdigit(c)) {
//             col += c - '0';
//         } else {
//             _board[row][col] = c;
//             col++;
//         }
//     }
// }

// vector<Move> ChessBoard::generate_move(char color) const {
//     vector<Move> moves;

//     for(int i = 0; i < ROW; i++) {
//         for(int j = 0; j < COL; j++) {
//             char piece = _board[i][j];

//             if(piece != '.' && ((isupper(piece) && color == 'w') || (islower(piece) && color == 'b'))) {
//                 switch (tolower(piece)) {
//                     case 'k':
//                         moves.insert(moves.end(), generate_king_move(i, j, color).begin(), generate_king_move(i, j, color).end());
//                         break;
                    
//                     case 'q':
//                     moves.insert(moves.end(), generate_queen_move(i, j, color).begin(), generate_queen_move(i, j, color).end());
//                         break;

//                     case 'r':
//                     moves.insert(moves.end(), generate_rock_move(i, j, color).begin(), generate_rock_move(i, j, color).end());
//                         break;

//                     case 'n': //knight
//                         moves.insert(moves.end(), generate_knight_move(i, j, color).begin(), generate_knight_move(i, j, color).end());
//                         break;

//                     case 'b':
//                     moves.insert(moves.end(), generate_bishop_move(i, j, color).begin(), generate_bishop_move(i, j, color).end());
//                         break;            
//                 }
//             }
//         }
//     }
//     return moves;
// }

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