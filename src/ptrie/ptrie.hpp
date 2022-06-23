#pragma once

#include <unordered_map>
#include <string>
#include <fstream>

#define ALL_MATCH -1

class TrieEdge;
class TrieNode;

class PTrie {
    private:
        
        int matchPrefixChars(const std::string &prefix, const std::string& word) const;
        TrieNode *_delete_rec(TrieNode *root, const std::string &word);

    public:TrieNode *root;
        PTrie();
        ~PTrie();

        void insert(const std::string &word);
        bool search(const std::string &word) const;
        void remove(const std::string &word);

        friend std::ostream& operator<<(std::ostream& os, const PTrie &other); // TODO
        friend std::istream& operator>>(std::istream& is, PTrie &other); // TODO

        // TODO IO Funcs

        void print(std::ostream &os);

        // TODO - Write to file

        friend void writeToFile();
        friend void writeToFile(const std::string &filename);
        friend void writeToFile(std::ofstream &f);

        // TODO - Read from file

        friend void readFromFile();
        friend void readFromFile(const std::string &filename);
        friend void readFromFile(std::ifstream &f);
};