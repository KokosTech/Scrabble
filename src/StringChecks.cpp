#include"StringChecks.hpp"
#include<iterator>

bool StringChecks::LetCheck(std::string str, std::map<char, int> letters)
{
    for(int i = 0; i < str.size(); i++)
    {
        std::map<char, int>::iterator itr;
        bool Nfound = 1;
        for(itr = letters.begin(); itr != letters.end(); itr++)
        {
            if(str[i] == itr->first)
            {
                itr->second--;
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
        return x + str.size() - 1 < 15;
    }else if(dir == 'V')
    {
        return y + str.size() - 1 < 15;
    }
    return 0;
}

bool StringChecks::BoardCheck(std::string str, size_t x, size_t y, char dir, char board[15][15], std::map<char, int> letters)
{
    if(dir == 'H')
    {
        bool OtherLet = 0;
        std::string neededLet = str;

        if(board[x-1][y] != '*')
        for(int i = 0; i < str.size(); i++)
        {
            if(board[x+i][y] != '*')
            {
                if(board[x+i][y] != str[i]) return 0;

                neededLet.erase(i, 1);
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
                if(temp.size > 1)
                {
                    //check if Temp is a real word;
                }
            }
        }

        for(; board[x-1][y] != '*' && x > 0; x--)
        {
            str = board[x-1][y] + str;
        }

        //Check if word is a word in tree
        for(int i = 0; i < str.size(); i++)
        {
            if(board[x+i][y] != '*')
            {
                std::map<char, int>::iterator itr;
                bool Nfound = 1;
                for(itr = letters.begin(); itr != letters.end(); itr++)
                {
                    if(str[i] == itr->first)
                    {
                        itr->second++;
                        Nfound = 0;
                        break;
                    }
                }
                if(Nfound)
                {
                    letters.insert(std::pair<char, int>(board[x+i][y], 1));
                }
            }
        }
        StringChecks::LetCheck(str, letters);

    }
}
