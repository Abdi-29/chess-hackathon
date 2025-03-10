#ifndef MOVE_HPP
#define MOVE_HPP

#include <string>

using namespace std;

class Move {
    private:
        int _from_c;
        int _from_r;
        int _to_c;
        int _to_r;

    public:
        Move(int fx, int fy, int tx, int ty);
        string to_algebraic_notation() const;
};

#endif