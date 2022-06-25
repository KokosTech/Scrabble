#pragma once
#include<string>
#include<map>


class StringChecks
{
public:

    static bool LetCheck(std::string str, std::map<char, int> letters);
    static bool PosCheck(std::string str, size_t x, size_t y, char dir);
    static bool BoardCheck(std::string str, size_t x, size_t y, char dir, char board[15][15], std::map<char, int> letters, bool first);
};
