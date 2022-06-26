#pragma once

class UMap;

class Menu {
    private:
        static void printMainMenu();
        static void printOptionsMenu();
        static void AddWord(UMap &map);
        static void Options();

    public:
        static int letters, rounds;

        static void clearScreen();
        static void cls();

        static int MainMenu(UMap &map);
};
