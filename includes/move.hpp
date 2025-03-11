#pragma once

#include <memory>
#include "piece.hpp"

struct Move {
    int from_row, from_col;
    int to_row, to_col;
    unique_ptr<Piece> captured_piece;
    char promotion_piece = '\0';
};
