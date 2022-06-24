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
        static std::set<char> getLetters(const std::vector<LetSort> &letters);
        static void validateInput(const std::string &const_input, const std::vector<LetSort> &letters, const PTrie &dictionary);
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters);

        ~Game();

        static int start(int letters, int rounds);
};
