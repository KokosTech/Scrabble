#pragma once

#include <vector>
#include <set>
#include <string>

class LetSort;
class PTrie;

class Game {
    private:
        unsigned char rounds;
        unsigned char letters;
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters);

        ~Game();

        static int start(int letters, int rounds);
};
