#pragma once

#include <string>
#include <unordered_map>

#define uint unsigned int

class Trie {
private:
    std::unordered_map<char, Trie*> characters;
    bool isEnd;

    // check if the string contains allowed characters
    bool checkString(const std::string& word);
    // helper function to output the words in the trie
    void outWords(std::ostream& os, const std::string& prefix);
public:
    Trie();
    ~Trie();

    // insert into trie
    bool insert(const std::string& word);
    // search for a word in the trie; if fount -> true else false
    bool search(const std::string& word);
    // remove a word from the trie; upon failiure an exception is thrown
    void remove(const std::string& word);
    // overloading operator<<
    friend std::ostream& operator<<(std::ostream& os, const Trie& other);
};