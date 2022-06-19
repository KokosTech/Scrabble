#pragma once

class Game {
    private:
        unsiged char rounds;
    public:
        Game() : rounds(10) { }
        Game(unsigned char rounds) : rounds(rounds) { }

        ~Game() { }

        void start();
};