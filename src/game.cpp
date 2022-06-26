#include "game.hpp"
#include "menu.hpp"
#include "SortedLetter.hpp"
#include "ptrie/ptrie.hpp"
#include "Board.hpp"
#include "umap/umap.hpp"

#include <iostream>
#include <random>
#include <exception>
#include <ctime>
#include <algorithm>
Game::Game()
: rounds(10), letters(10) { }
Game::Game(unsigned char rounds, unsigned char letters) : rounds(rounds), letters(letters), green() {}


int Game::start(int lettersSize, int rounds, UMap &dictionary)
{
    int points = 0;
    int i = 0;
    PTrie trie;
    
    dictionary = dictionary.ToUpperCase(dictionary);
    trie.getFromDictionary(dictionary.getWords());

    srand(time(NULL));
    while(i < rounds)
    {
        Menu::cls();
        this->green.printBoard();
        std::cout<<"Your given letters are: ";
        std::map<char, int> letters;
        for(int y = 0; y < lettersSize; y++)
        {
            char tempC = rand() % 26 + 65;
            bool Nfound = 1;
            std::cout<<tempC<<" ";
            for( std::map<char, int>::iterator itr = letters.begin(); itr != letters.end(); itr++)
            {
                if(tempC == itr->first)
                {
                    itr->second++;
                    Nfound = 0;
                    break;
                }
            }
            if(Nfound)
            {
                letters.insert(std::pair<char, int>(tempC, 1));
            }
        }
        std::cout << "\nEnter a word with the given letters, column and row of the word and direction(H/V). To draw new letters enter 0: ";
        std::string input;
        int x, y;
        char dir;
        std::cin >> input;
        if(input == "0")
        {
            continue;
        }
        std::cin >> x >> y;
        std::cin >> dir;



        if(!green.AddWord(input, dir, x-1, y-1, letters, i == 0, trie))
        {
            std::cout<<"Invalid inputs. Press enter to continue...";
            getchar();
            getchar();
            continue;
        }

        //Check if the word is Possible with given letters and if its a real word
        try {
            trie.remove(input);
            ++i;
        } catch(const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
    return points;
}

Game::~Game(){}
