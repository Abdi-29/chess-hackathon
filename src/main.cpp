#include <iostream>
#include "../includes/chessboard.hpp"

int main(void) {
    ChessBoard board;
    string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    board.parse_fen(fen);
}