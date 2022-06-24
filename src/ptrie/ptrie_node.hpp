#pragma once

#include "ptrie_edge.hpp"

#include <unordered_map>
#include <string>

class TrieNode {
    private:
        bool isEnd;
        std::unordered_map<char, TrieEdge*> children;

        void validate(char firstCharacter) const;
    public:
        TrieNode();        
        TrieNode(bool isEnd);
        TrieNode(const TrieNode &other);

        TrieNode &operator=(const TrieNode &other);

        ~TrieNode();
        
        void addEdge(char firstCharacter, TrieEdge *edge);
        void addEdge(const std::string &prefix, TrieNode *node);
        bool checkIfEdgeExists(char firstCharacter) const;
        void removeEdge(char firstCharacter); 
        bool hasEdges();

        void setIsEnd(bool isEnd);
        bool getIsEnd() const;
        TrieEdge *getEdge(char firstCharacter) const;
        const std::unordered_map<char, TrieEdge*> &getEdges() const;
        unsigned int getEdgeCount() const;

        friend std::ostream& operator<<(std::ostream& os, const TrieNode &other); // TODO
};  

void addEdgeToTrieNode(TrieNode *node, char firstCharacter, const std::string &prefix, bool edgeNodeIsEnd);
