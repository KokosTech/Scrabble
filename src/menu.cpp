#include <iostream>
#include "menu.hpp"

void Menu::clearScreen() {
    std::cout << "\033[2J\033[1;1H";
}

void Menu::printMenu() {
    clearScreen();
    std::cout << "======== MENU ========\n";
    std::cout << "1. Start game\n";
    std::cout << "2. Settings\n";
    std::cout << "3. Add work do dictionary\n";
    std::cout << "4. Exit\n";
    std::cout << "======================\n";
    std::cout << "Enter: ";
}

void Menu::menu() {
    printMenu();
}