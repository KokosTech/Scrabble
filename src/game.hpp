#pragma once

#include "Board.hpp"
#include <vector>
#include <set>
#include <string>

class LetSort;
class PTrie;

class Game {
    private:
        unsigned char rounds;
        unsigned char letters;
        Board green;
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters);

        ~Game();

        int start(int letters, int rounds);
};
