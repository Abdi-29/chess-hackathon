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
    // active_color = 'w';
    halfmove_clock = 0;
    fullmove_number = 1;
    initialize_board();
}

void ChessBoard::clear_board() {
    for(int i = 0; i < COL; i++) {
        for(int j = 0; j < ROW; j++) {
            board[i][j] = nullptr;
        }
    }
}

void ChessBoard::parse_fen(const string& fen) {
    istringstream iss(fen);
    string pieces;
    iss >> pieces >> active_color;

    cout << "parse_fen: " << fen << endl;
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
                case 'r': board[row][col] =  make_unique<Rock>(is_white); break;
                case 'n': board[row][col] =  make_unique<Knight>(is_white); break;
                case 'p': board[row][col] =  make_unique<Pawn>(is_white); break;
                case 'k': board[row][col] =  make_unique<King>(is_white); update_king_position(row, col, is_white); break;
                case 'q': board[row][col] =  make_unique<Queen>(is_white); break;
                case 'b': board[row][col] =  make_unique<Bishop>(is_white); break;   
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
    while(getline(file, fen)) {
        if(getline(file, moves_line)) {
            istringstream iss(moves_line);
            string move;
            vector<string> moves;
            while(iss >> move) {
                moves.push_back(move);
            }
            opening_book.emplace(fen, std::move(moves));
        }
    }
}

string ChessBoard::get_best_move_from_book(const string& fen) {
    istringstream iss(fen);
    string piece_placement, active_color, castling_rights, en_passant, halfmove_clock, fullmove_number;
    iss >> piece_placement >> active_color >> castling_rights >> en_passant >> halfmove_clock >> fullmove_number;
        auto it = opening_book.find(fen);
        if(it != opening_book.end() && !it->second.empty()) {
            const auto& moves = it->second;
            return moves[0];
        }
    
    return "";
}

ChessBoard::Move ChessBoard::parse_move(const std::string& move_str) {
    Move move;
    move.from_col = move_str[0] - 'a';
    move.from_row = move_str[1] - '1';
    move.to_col = move_str[2] - 'a';
    move.to_row = move_str[3] - '1';

    if(move_str.length() == 5) {
        move.promotion_piece = tolower(move_str[4]);
    }
    // TODO: Add castling and en passant detection
    return move;
}

void ChessBoard::make_move(const Move& move) {
    board[move.to_row][move.to_col] = std::move(board[move.from_row][move.from_col]);
    board[move.from_row][move.from_col] = nullptr;

    bool is_capture = (board[move.to_row][move.to_col] != nullptr);
    bool is_pawn_move = (board[move.to_row][move.to_col] && board[move.to_row][move.to_col]->type == 'p');

    if (is_capture || is_pawn_move) {
        halfmove_clock = 0;
    } else {
        halfmove_clock++;
    }

    if(board[move.to_row][move.to_col]->type == (active_color == 'w' ? 'K' : 'k')) {
        update_king_position(move.to_row, move.to_col, active_color == 'w');
    }

    if(move.promotion_piece != '\0') {
        bool is_white = active_color == 'w';
        switch (move.promotion_piece) {
            case 'q': board[move.to_row][move.to_col] = make_unique<Queen>(is_white); break;
            case 'r': board[move.to_row][move.to_col] = make_unique<Rock>(is_white); break;
            case 'b': board[move.to_row][move.to_col] = make_unique<Bishop>(is_white); break;
            case 'n': board[move.to_row][move.to_col] = make_unique<Knight>(is_white); break;
        }
    }

    if (active_color == 'b') {
        fullmove_number++;
    }
    active_color = (active_color == 'w') ? 'b' : 'w';
}

bool ChessBoard::is_king_in_check(char color) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (board[row][col] && board[row][col]->is_white != (color == 'w')) {
                auto moves = board[row][col]->get_moves(row, col, board);
                for (auto [to_row, to_col] : moves) {
                    if (to_row == king_pos[0] && to_col == king_pos[1]) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}


string ChessBoard::getFEN() {
    string fen;
    for(int row = 7; row >= 0; --row) {
        int empty_count = 0;
        for(int col = 0; col < 8; ++col) {
            if(!board[row][col]) {
                empty_count++;
            } else {
                if(empty_count > 0) {
                    fen += to_string(empty_count);
                    empty_count = 0;
                }
                char fen_char = board[row][col]->is_white ? toupper(board[row][col]->type) : board[row][col]->type;
                fen += fen_char;
            }
        }
        if(empty_count > 0) {
            fen += to_string(empty_count);
        }
        if(row > 0) {
            fen += '/';
        }
    }
    fen += " " + string(1, active_color) + " KQkq - " + to_string(halfmove_clock) + " " + to_string(fullmove_number);
    return fen;
}

vector<ChessBoard::Move>& ChessBoard::generate_legal_moves() {
    vector<Move> moves;
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            if (board[row][col] && board[row][col]->is_white == (active_color == 'w')) {
                auto piece_moves = board[row][col]->get_moves(row, col, board);
                
                for (auto [to_row, to_col] : piece_moves) {
                    Move move{row, col, to_row, to_col};
                    ChessBoard temp_board = *this;
                    temp_board.make_move(move);

                    if (!temp_board.is_king_in_check(active_color)) {
                        moves.push_back(move);
                    }
                }
            }
        }
    }
    return moves;
}

void ChessBoard::uci_position(istringstream& iss, const string& default_fen) {
    string token;
    iss >> token;

    clear_board();
    fullmove_number = 1;
    if(token == "startpos") {
        parse_fen(default_fen);
    } else if(token == "fen") {
        string fen;
        while(iss >> token && token != "moves") {
            fen += token + " ";
        }
        parse_fen(fen);
    }

    if(iss >> token && token.starts_with("moves")) {
        while(iss >> token) {
            cout << "token: " << token << endl;
            Move move = parse_move(token);
            make_move(move);
        }
    }
}

void ChessBoard::uci_go(istringstream& iss) {
    string token;
    int depth = 4;
    int movetime = -1;

    while(iss >> token) {
        if(token == "depth") {
            iss >> depth;
        } else if(token == "movetime") {
            iss >> movetime;
        }
    }

    string best_move;
    string current_fen = getFEN();

    best_move = get_best_move_from_book(current_fen);
    if(best_move.empty()) {
        best_move = get_best_move(depth, movetime);
    }

    cout << "bestmove " << best_move << endl;
}

string ChessBoard::move_to_uci(const Move& move) {
    char from_file = 'a' + move.from_col;  
    char to_file = 'a' + move.to_col;  
    int from_rank = move.from_row + 1;  
    int to_rank = move.to_row + 1;  

    return string(1, from_file) + to_string(from_rank) +
           string(1, to_file) + to_string(to_rank);
}



string ChessBoard::get_best_move(int depth, int movetime) {
    // vector<Move> legal_moves = generate_legal_moves();

    // if (legal_moves.empty()) {
    //     return "";
    // }

    // // TODO: Alpha-Beta Pruning here

    // Move best_move = legal_moves[0];
    // return move_to_uci(best_move);
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