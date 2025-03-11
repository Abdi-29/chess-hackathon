#include "move.hpp"

// Move::Move(int fx, int fy, int tx, int ty): _from_c(fx), _from_r(fy), _to_c(tx), _to_r(ty) {}

/*
    https://www.chessprogramming.org/Algebraic_Chess_Notation

    <move descriptor> ::= <from square><to square>[<promoted to>]
    <square>        ::= <file letter><rank number>
    <file letter>   ::= 'a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'
    <rank number>   ::= '1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'
    <promoted to>   ::= 'q'|'r'|'b'|'n'
 */
// string Move::to_algebraic_notation() const {
//     char from_square = 'a' + _from_c;
//     char to_square = 'a' + _to_c;
//     int from_rank = _from_r + 1;
//     int to_rank = _to_r + 1;

//     //TODO promoted to
    
//     return string(1, from_square) + to_string(from_rank) + string(1, to_square) + to_string(to_rank);
// }