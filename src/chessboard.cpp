#include "chessboard.hpp"
#include <sstream>
#include <cctype>

ChessBoard::ChessBoard() {
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            _board[i][j] = '.';
        }
    }
    _active_color = 'w';
}

void ChessBoard::parse_fen(const string& fen) {
    istringstream iss(fen);
    string pieces;
    iss >> pieces >> _active_color;

    cout << "pieces: " << pieces << endl;
    cout << "color: " << _active_color << endl;

    int start = 0;
    int end = pieces.find('/');
    int row = ROW - 1;

    while(end != string::npos) {
        string rank = pieces.substr(start, end - start);
        fill_board(rank, row);
        start = end + 1;
        end = pieces.find('/', start);
        row--;
    }

    string rank = pieces.substr(start);
    fill_board(rank, row);
    // print_board();
}

void ChessBoard::fill_board(const string& rank, int row) {
    int col = 0;

    for(char c: rank) {
        if(isdigit(c)) {
            col += c - '0';
        } else {
            _board[row][col] = c;
            col++;
        }
    }
}

vector<Move> ChessBoard::generate_move(char color) const {
    vector<Move> moves;

    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            char piece = _board[i][j];

            if(piece != '.' && ((isupper(piece) && color == 'w') || (islower(piece) && color == 'b'))) {
                switch (tolower(piece)) {
                    case 'k':
                        moves.insert(moves.end(), generate_king_move(i, j, color).begin(), generate_king_move(i, j, color).end());
                        break;
                    
                    case 'q':
                    moves.insert(moves.end(), generate_queen_move(i, j, color).begin(), generate_queen_move(i, j, color).end());
                        break;

                    case 'r':
                    moves.insert(moves.end(), generate_rock_move(i, j, color).begin(), generate_rock_move(i, j, color).end());
                        break;

                    case 'n': //knight
                        moves.insert(moves.end(), generate_knight_move(i, j, color).begin(), generate_knight_move(i, j, color).end());
                        break;

                    case 'b':
                    moves.insert(moves.end(), generate_bishop_move(i, j, color).begin(), generate_bishop_move(i, j, color).end());
                        break;            
                }
            }
        }
    }
    return moves;
}

void ChessBoard::print_board() {
    for(int i = 0; i < ROW; i++) {
        for(int j = 0; j < COL; j++) {
            cout << _board[i][j];
        }
        cout << endl;
    }
}