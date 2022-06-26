#pragma once

#include <unordered_map>
#include <string>

class TrieEdge;

class TrieNode {
    private:
        bool isEnd;
        int endIndex;
        std::unordered_map<char, TrieEdge*> children;

        void validate(char firstCharacter) const;
    public:
        TrieNode();        
        TrieNode(bool isEnd);
        TrieNode(bool isEnd, int endIndex);
        TrieNode(const TrieNode &other);
        TrieNode &operator=(const TrieNode &other);

        ~TrieNode();
        
        void addEdge(char firstCharacter, TrieEdge *edge);
        void addEdge(const std::string &prefix, TrieNode *node);
        void addEdge(char firstCharacter, const std::string &prefix, bool edgeNodeIsEnd, int endIndex);

        void changeEdge(char firstCharacter, TrieEdge *edge);
        void removeEdge(char firstCharacter); 
        
        bool checkIfEdgeExists(char firstCharacter) const;
        bool hasEdges();

        void setIsEnd(bool isEnd);
        void setEndIndex(int endIndex);
        bool getIsEnd() const;
        int getEndIndex() const;
        TrieEdge *getEdge(char firstCharacter) const;
        const std::unordered_map<char, TrieEdge*> &getEdges() const;        unsigned int getEdgeCount() const;


        friend std::ostream& operator<<(std::ostream& os, const TrieNode &other); // TODO
};