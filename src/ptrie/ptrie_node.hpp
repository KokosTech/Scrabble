#pragma once

#include <unordered_map>
#include <string>

class TrieEdge;

class TrieNode {
    private:
        bool isEnd;
        std::unordered_map<char, TrieEdge*> children;

        void validate(char firstCharacter) const;
    public:
        TrieNode();        
        TrieNode(bool isEnd);
        ~TrieNode();
        
        void addEdge(char firstCharacter, TrieEdge *edge);
        bool checkIfEdgeExists(char firstCharacter) const;
        void removeEdge(char firstCharacter); 
        
        void setIsEnd(bool isEnd);
        bool getIsEnd() const;
        TrieEdge *getEdge(char firstCharacter) const;
};  

void addEdgeToTrieNode(TrieNode *node, char firstCharacter, const std::string &prefix, bool edgeNodeIsEnd);
