#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <fstream>

#define ALL_MATCH -1

class TrieEdge;
class TrieNode;

class PTrie {
    private:
        TrieNode *root;
        
        void _copyConstructor(TrieNode *thisRoot, TrieNode *otherRoot);
        void _getWordRec(TrieNode *root, const std::string &prefix, std::vector<std::string> &words) const;

        int matchPrefixChars(const std::string &prefix, const std::string& word) const;
        TrieNode *_delete_rec(TrieNode *root, const std::string &word);

    public:
        PTrie();
        PTrie(const PTrie &other);

        PTrie &operator=(const PTrie &other);

        ~PTrie();

        // Funcs
        
        void changeEdge(char firstCharacter, TrieEdge *edge);
        void _insert(TrieNode *current, const std::string &word);

        void insert(const std::string &word);
        bool search(const std::string &word) const;
        void remove(const std::string &word);

        // Getters and setters

        const TrieNode &getRoot() const;
        std::vector<std::string> getWords() const;

        // IO Streams

        friend std::ostream& operator<<(std::ostream& os, const PTrie &other); // TODO
        friend std::istream& operator>>(std::istream& is, PTrie &other); // TODO

        // IO Funcs

        void print();

        // Write to file

        friend void writeToFile(const std::string &filename, PTrie &other);
        friend void writeToFile(std::ofstream &f, PTrie &other);

        // Read from file

        friend void readFromFile(const std::string &filename, PTrie &other);
        friend void readFromFile(std::ifstream &f, PTrie &other);
};