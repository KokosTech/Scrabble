#include "game.hpp"
#include "menu.hpp"
#include "SortedLetter.hpp"
#include "ptrie/ptrie.hpp"

#include <iostream>
#include <random>
#include <exception>
#include <ctime>
#include <algorithm>

Game::Game() 
: rounds(10), letters(10) { }
Game::Game(unsigned char rounds, unsigned char letters) : rounds(rounds), letters(letters) { }

std::set<char> Game::getLetters(const std::vector<LetSort> &letters) {
    std::set<char> s;
    std::vector<LetSort>::const_iterator it = letters.begin();
    for(it; it != letters.end(); ++it) {
        s.insert(it->getLet());
    }

    return s;
}

void Game::validateInput(const std::string &const_input, const std::vector<LetSort> &letters, const PTrie &dictionary) {
    std::set<char> lettersSet = Game::getLetters(letters);
    
    std::string input = const_input;
    std::transform(input.begin(), input.end(),input.begin(), ::toupper);

    for(int i = 0; i < input.length(); ++i) {
        if(lettersSet.find(input[i]) == lettersSet.end()) {
            throw std::runtime_error("Only given letters must be used!");
        }   
    }

    if(!dictionary.search(input)) {
        throw std::runtime_error("Word is invalid - it is not present in the dictionary or is already used by another player!");
    }
}

int Game::start(int lettersSize, int rounds)
{
    int points = 0;
    int i = 0;
    PTrie dictionary;

    //TODO: ADD READING DICTIONARY FROM FILE

    while(i < rounds)
    {
        Menu::cls();
        std::cout<<"Your given letters are: ";
        std::vector<LetSort> letters;
        for(int y = 0; y < lettersSize; y++)
        {
            char tempC = rand() % 26 + 65;
            bool Nfound = 1;
            std::cout<<tempC<<" ";
            for(int z = 0; z < letters.size(); z++)
            {
                if(tempC == letters[z].getLet())
                {
                    letters[z].Addcount();
                    letters[z].setFake();
                    Nfound = 0;
                    break;
                }
            }
            if(Nfound)
            {
                LetSort temp(tempC);
                temp.setFake();
                letters.push_back(temp);
            }
        }
        std::cout << "\nEnter a word with the given letters: ";
        std::string input;
        std::cin >> input;

        //Check if the word is Possible with given letters and if its a real word
        try {
            Game::validateInput(input, letters, dictionary);
            // dictionary.remove(input);
            //TODO: Add points logic
            ++i;
        } catch(const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return points;
}