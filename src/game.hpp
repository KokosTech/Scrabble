#pragma once

class Game {
    private:
        unsinged char rounds;
        unsinged char letters
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters) : rounds(rounds), letters(letters) { }

        ~Game() { }

        void start();
};