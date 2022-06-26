#include "menu.hpp"

#include <iostream>

void Menu::clearScreen() {
    std::cout << "\033[2J\033[1;1H\n";
}

void Menu::cls() {
    std::cout<<"Press enter to continue...";
    getchar();
    getchar();
    clearScreen();
}

void Menu::printMainMenu() {
    clearScreen();
    std::cout << "======== MENU ========\n";
    std::cout << "1. Start game\n";
    std::cout << "2. Settings\n";
    std::cout << "3. Add work do dictionary\n";
    std::cout << "4. Exit\n";
    std::cout << "======================\n";
    std::cout << "Enter: ";
}

void Menu::printOptionsMenu() {
    clearScreen();
    std::cout << "======== OPTIONS ========\n";
    std::cout << "1. Change number of letters\n";
    std::cout << "2. Change number of rounds\n";
    std::cout << "3. Exit to main menu\n";
    std::cout << "==========================\n";
    std::cout << "Enter: ";
}


void Menu::Options() {
    while(true) {
        int input;

        printOptionsMenu();

        std::cin >> input;

        switch(input) {
            case 1:
                std::cout << "Enter new number of letters:";
                std::cin >> Menu::letters;
                cls();
                break;
            case 2:
                std::cout << "Enter new number of rounds:";
                std::cin >> Menu::rounds;
                cls();
                break;
            case 3:
                return;
            default:
                std::cout << "Invalid input." << std::endl;
                cls();
                break;
        }
    }
}

int Menu::MainMenu() {
    letters = 10;
    rounds = 10;

    while(true) {
        int input;

        printMainMenu();

        std::cin >> input;

        switch(input) {
            case 1:
                return 1;
            case 2:
                Options();
                break;
            case 3:
                std::cout<<"Add new word to dictionary:";
                std::string word;
                std::cin>>word;
                //AddWord(word);
                break;
            case 4:
                return 0;
            default:
                std::cout<<"Invalid input."<<std::endl;
                cls();
                break;
        }
    }
}

int Menu::letters = 10;
int Menu::rounds = 10;
