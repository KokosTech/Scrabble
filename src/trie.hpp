#pragma once

#include <string>
#include <unordered_map>

#define NUM_CHARS 26

class Trie {
private:
    std::unordered_map<char, Trie*> characters;
    bool isEnd;
public:
    Trie();
    ~Trie();
    bool insert(const std::string& word);
    bool search(const std::string& word);
    void remove(const std::string& word);
};