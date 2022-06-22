#pragma once

#include <unordered_map>
#include <string>

#define ALL_MATCH -1

class Edge;
class TrieNode;

class PTrie {
    private:
        TrieNode *root;
        int matchPrefixChars(const std::string &prefix, const std::string& word);
    public:
        PTrie();
        ~PTrie();

        void insert(const std::string &word);
        bool search(const std::string &word); // TODO
        bool remove(const std::string &word); // TODO

        friend std::ostream& operator<<(std::ostream& os, const PTrie &other); // TODO
        friend std::istream& operator>>(std::istream& is, const PTrie &other); // TODO
};