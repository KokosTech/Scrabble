#include"StringChecks.hpp"
#include<iterator>
#include<iostream>

bool StringChecks::LetCheck(std::string str, std::map<char, int> letters)
{
    for(int i = 0; i < str.size(); i++)
    {
        std::map<char, int>::iterator itr;
        bool Nfound = 1;
        for(itr = letters.begin(); itr != letters.end(); itr++)
        {
            if(str[i] == itr->first || str[i] - 32 == itr->first)
            {
                itr->second--;
                if(itr->second < 0)return 0;
                Nfound = 0;
                break;
            }
        }
        if(Nfound)
        {
            return 0;
        }
    }
    return 1;
}
bool StringChecks::PosCheck(std::string str, size_t x, size_t y, char dir)
{
    if(dir == 'H')
    {
        return x + str.size() < 15;
    }else if(dir == 'V')
    {
        return y + str.size() < 15;
    }
    return 0;
}

bool StringChecks::BoardCheck(std::string str, size_t x, size_t y, char dir, char board[15][15], std::map<char, int> letters, bool first)
{
    if(!PosCheck(str, x, y, dir))return 0;
    //Check if str is a word from the tree
    if(dir == 'V')
    {
        bool OtherLet = 0;
        std::string neededLet = str;
        size_t deleted = 0;
        std::cout<<neededLet<<std::endl;
        if(x > 0 && board[x-1][y] != '*'){std::cout<<"++Case 1++";return 0;}
        if(x + str.size() - 1 < 15 && board[x + str.size()][y] != '*'){std::cout<<"++Case 2++";return 0;}
        for(int i = 0; i < str.size(); i++)
        {
            if(board[x+i][y] != '*')
            {
                if(board[x+i][y] != str[i]){std::cout<<"++Case 2++";return 0;}

                neededLet.erase(i - deleted, 1);
                deleted++;
                std::cout<<neededLet<<std::endl;
                OtherLet = 1;
            }else
            {
                std::string temp = "" + board[x+i][y];
                for(int z = y + 1; board[x+i][z] != '*' && z < 15; z++)
                {
                    temp += board[x+i][z];
                    OtherLet = 1;
                }

                for(int z = y - 1; board[x+i][z] != '*' && z >= 0; z--)
                {
                    temp += board[x+i][z];
                    OtherLet = 1;
                }
                if(temp.size() > 1)
                {
                    //check if Temp is a real word;
                }
            }
        }
        if(!OtherLet && !first){std::cout<<"++Case 4++";return 0;}
        if(!StringChecks::LetCheck(neededLet, letters)){std::cout<<"++Case 5++";return 0;}
    }

    if(dir == 'H')
    {
        bool OtherLet = 0;
        std::string neededLet = str;
        int deleted = 0;
        std::cout<<neededLet<<std::endl;

        if(y > 0 && board[x][y - 1] != '*'){std::cout<<"++Case 6++";return 0;}
        if(y + str.size() - 1 < 15 && board[x][y + str.size()] != '*'){std::cout<<"++Case 7++";return 0;}
        for(int i = 0; i < str.size(); i++)
        {
            if(board[x][y+i] != '*')
            {
                if(board[x][y+i] != str[i]){std::cout<<"++Case 8++";return 0;}

                neededLet.erase(i - deleted, 1);
                deleted++;
                std::cout<<neededLet<<std::endl;
                OtherLet = 1;
            }else
            {
                std::string temp = "" + board[x][y+i];
                for(int z = x + 1; board[z][y+i] != '*' && z < 15; z++)
                {
                    temp += board[z][y+i];
                    OtherLet = 1;
                }

                for(int z = x - 1; board[z][y+i] != '*' && z >= 0; z--)
                {
                    temp += board[z][y+i];
                    OtherLet = 1;
                }
                if(temp.size() > 1)
                {
                    //check if Temp is a real word;
                }
            }
        }
        if(!OtherLet && !first){std::cout<<"++Case 9++";return 0;}
        if(!StringChecks::LetCheck(neededLet, letters)){std::cout<<"++Case 10++";return 0;}
    }
    return 1;
}
