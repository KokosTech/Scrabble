#include"Board.hpp"

#include<iostream>

Board::Board()
{
    for(int i = 0; i < 15; i++)
    {
        for(int y = 0; y < 15; y++)
        {
            this->tiles[i][y] = '*';
        }
    }
}

void Board::printBoard()
{
    for(int i = 0; i < 15; i++)
    {
        for(int y = 0; y < 15; y++)
        {
            std::cout<<this->tiles[i][y];
        }
        std::cout<<std::endl;
    }
}

void AddFirstWord(std::string word, char dir, size_t x, size_t y, map<char, int> letters)
{

}
