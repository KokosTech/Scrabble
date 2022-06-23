#include "game.hpp"
#include "SortedLetter.hpp"

#include <iostream>
#include <random>
#include <ctime>

Game::Game() 
: rounds(10), letters(10) { }
Game::Game(unsigned char rounds, unsigned char letters) : rounds(rounds), letters(letters) { }

std::set<char> Game::getLetters(const std::vector<LetSort> &letters) {
    std::set<char> s;
    std::vector<LetSort>::const_iterator it = letters.begin();
    for(it; it < letters.end(); ++it) {
        s.insert(it->getLet());
    }

    return s;
}

bool Game::validateLetters(const std::string &word, const std::vector<LetSort> &letters) {
    std::set<char> lettersSet = Game::getLetters(letters);

    for(int i = 0; i < word.length(); ++i) {
        if(lettersSet.find(word[0]) == lettersSet.end()) {
            throw std::runtime_error("Only the given capital letters must be used!");
        }   
    }

    return true;
}

int Game::start(int lettersSize, int rounds)
{
    int points = 0;
    for(int i = 0; i < rounds; i++)
    {
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
        Game::validateLetters(input, letters);
    }
    return points;
}


