#pragma once

#include <string>

class TrieNode;

class TrieEdge {
    private:
        std::string prefix;
        TrieNode *node;
    public:
        TrieEdge(const std::string &prefix);
        TrieEdge(const std::string &prefix, TrieNode *node);
        void setPrefix(const std::string &prefix);
        void setNode(TrieNode *node);
        const std::string &getPrefix() const;
        TrieNode *getNode() const;
        ~TrieEdge();
};
