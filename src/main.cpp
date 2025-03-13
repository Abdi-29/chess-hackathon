#include <iostream>
#include "../includes/chessboard.hpp"
#include <sstream>
#include <fstream>

int main(void) {
    ChessBoard board;
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    // board.parse_fen(fen);
    // // board.print_board();
    // board.load_opening_book();
    // cout << board.get_best_move_from_book(fen) << endl;
    string command;
    board.load_opening_book();

    while(true) {
        getline(cin, command);
        istringstream iss(command);
        string token;
        iss >> token;

        if(token == "uci") {
            cout << "id name abba\nid author ab\nuciok\n";
        } 
        else if(token == "isready") {
            cout << "readyok\n";
        } 
        else if(token == "position") {
            board.uci_position(iss, fen);
        } 
        else if(token == "go") {
            board.uci_go(iss);
        } 
        else if(token == "quit") {
            break;
        }
    }
}

void uciLoop() {
    
}
