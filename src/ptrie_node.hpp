#pragma once

#include <unordered_map>
#include <string>

class TrieEdge;

class TrieNode {
    private:
        bool isEnd;
        std::unordered_map<char, TrieEdge*> children;
    public:
        TrieNode();        
        TrieNode(bool isEnd);
        ~TrieNode();
        void setIsEnd(bool isEnd);
        void addEdge(char firstCharacter, TrieEdge *edge);
        bool checkIfEdgeExists(char firstCharacter) const;
        void removeEdge(char firstCharacter); 
        TrieEdge *getEdge(char firstCharacter) const;
        bool getIsEnd() const;
};  