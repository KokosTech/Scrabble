#pragma once

#include <unordered_map>
#include <string>

#define ALL_MATCH -1

class TrieEdge;
class TrieNode;

class PTrie {
    private:
        
        int matchPrefixChars(const std::string &prefix, const std::string& word);
        TrieNode *_delete_rec(TrieNode *root, TrieEdge *edge, const std::string &word);

    public:TrieNode *root;
        PTrie();
        ~PTrie();

        void insert(const std::string &word);
        bool search(const std::string &word);
        void remove(const std::string &word);

        friend std::ostream& operator<<(std::ostream& os, const PTrie &other); // TODO
        friend std::istream& operator>>(std::istream& is, PTrie &other); // TODO
};