#pragma once


class Game {
    private:
        unsinged char rounds;
        unsinged char letters;
    public:
        Game();
        Game(unsigned char rounds, unsigned char letters);

        ~Game();

        void start();
};
