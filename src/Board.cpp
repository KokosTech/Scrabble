#include"Board.hpp"
#include"StringChecks.hpp"
#include "ptrie/ptrie.hpp"

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
    std::cout<<"   ";
    for(int y = 0; y < 9; y++)
    {
        std::cout<<y + 1<<"  ";
    }
    for(int y = 9; y < 15; y++)
    {
        std::cout<<y + 1<<" ";
    }
    std::cout<<std::endl;
    for(int i = 0; i < 9; i++)
    {
        std::cout<<i + 1<<"  ";
        for(int y = 0; y < 15; y++)
        {
            std::cout<<this->tiles[i][y]<<"  ";
        }
        std::cout<<std::endl;
    }
    for(int i = 9; i < 15; i++)
    {
        std::cout<<i + 1<<" ";
        for(int y = 0; y < 15; y++)
        {
            std::cout<<this->tiles[i][y]<<"  ";
        }
        std::cout<<std::endl;
    }
}

bool Board::AddWord(std::string word, char dir, size_t x, size_t y, std::map<char, int> letters, bool first, PTrie &pt)
{
    if(pt.search(word) == -1) return 0; 

    for(int i = 0; i < word.size(); i++)word[i] = toupper(word[i]);

    if(StringChecks::BoardCheck(word, x, y, dir, this->tiles, letters, first))
    {
        if(dir == 'V')
        {
            for(int i = 0; i < word.size(); i++)
            {
                this->tiles[x+i][y] = word[i];
            }
        }else
        {
            for(int i = 0; i < word.size(); i++)
            {
                this->tiles[x][y+i] = word[i];
            }
        }
        return 1;
    }else{return 0;}
}
