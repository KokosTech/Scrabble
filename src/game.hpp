#pragma once
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
