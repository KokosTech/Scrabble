class Menu {
    private:
        static void clearScreen();

        static void cls();

        static void printMainMenu();
        static void printOptionsMenu();
        
        static void Options();

    public:
        static int letters, rounds;
        
        static int MainMenu();
};
