#pragma once
#include<string>
#include<map>

class Board
{
    char tiles[15][15];
public:

    Board();
    void AddFirstWord(std::string word, char dir, size_t x, size_t y, map<char, int> letters);
    void AddWord(std::string word, char dir, size_t x, size_t y, map<char, int> letters);

    void printBoard();

};
