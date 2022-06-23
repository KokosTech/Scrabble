#pragma once

#include <vector>
#include <set>
#include <string>

class LetSort;

class Game {
    private:
        unsigned char rounds;
        unsigned char letters;
        static std::set<char> Game::getLetters(const std::vector<LetSort> &letters);
        static bool validateLetters(const std::string &word, const std::vector<LetSort> &letters);
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters);

        ~Game();

        static int start(int letters, int rounds);
};
