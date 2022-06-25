#pragma once
#include<string>
#include<map>

class Board
{
    char tiles[15][15];
public:

    Board();
    bool AddWord(std::string word, char dir, size_t x, size_t y, std::map<char, int> letters, bool first);

    void printBoard();

};
