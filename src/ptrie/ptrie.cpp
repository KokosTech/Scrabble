#include "ptrie.hpp"
#include "ptrie_edge.hpp"
#include "ptrie_node.hpp"

#include <iostream>
#include <exception>

PTrie::PTrie() { this->root = new TrieNode(); }

PTrie::~PTrie() { delete this->root; }

// Helpers

int PTrie::matchPrefixChars(const std::string &prefix, const std::string &word) {
    for(unsigned int i = 0; i < prefix.length() && i < word.length(); ++i)
        if(word[i] != prefix[i]) return i;
    
    return ALL_MATCH;
}

// Funcs

void PTrie::insert(const std::string &word) {
    TrieNode *currNode = this->root;
    unsigned int currIndex = 0;

    if(word.empty()) throw std::invalid_argument("Cannot insert an empty string!");

    // Worst case scenario
    while(currIndex < word.length()) {
        TrieEdge *currEdge = currNode->getEdge(word[currIndex]);
        std::string currWordPart = word.substr(currIndex);

        if(currEdge == nullptr) {
            TrieNode *newnode = new TrieNode(true);
            TrieEdge *newedge = new TrieEdge(currWordPart, newnode);     

            currNode->addEdge(currWordPart[0], newedge);
            break;
        } 

        int matchIndex = matchPrefixChars(currEdge->getPrefix(), currWordPart);
        
        if(matchIndex == ALL_MATCH) {
            if(currEdge->getPrefix().length() == currWordPart.length()) {
                currEdge->getNode()->setIsEnd(true);
                break;
            } else if (currEdge->getPrefix().length() < currWordPart.length()) {
                matchIndex = currEdge->getPrefix().length();
            } else {
                std::string temp = currEdge->getPrefix().substr(matchIndex);
                // redundant - new addEdge
                // TrieNode *newnode = new TrieNode(false);
                // TrieEdge *newedge = new TrieEdge(temp, newnode);
                currEdge->setPrefix(currEdge->getPrefix().substr(0, matchIndex));
                
                // currEdge->getNode()->addEdge(temp[0], newedge);
                addEdgeToTrieNode(currEdge->getNode(), temp[0], temp, false);
                currEdge->getNode()->setIsEnd(true);
            }
        } else {
            TrieNode *tempNode = currEdge->getNode();
            std::string temp = currEdge->getPrefix().substr(matchIndex);

            // TrieNode *newnode = new TrieNode(currEdge->getNode()->getIsEnd());
            addEdgeToTrieNode(currEdge->getNode(), temp[0], temp, tempNode->getIsEnd());
           
            currEdge->getNode()->setIsEnd(false);
            // TrieEdge *newedge = new TrieEdge(currEdge->getPrefix().substr(matchIndex), newnode);
            currEdge->setPrefix(currEdge->getPrefix().substr(0, matchIndex));
            // currEdge->getNode()->addEdge(temp[0], newedge);
        }

        currNode = currEdge->getNode();
        currIndex += matchIndex;
    }
}

// TODO - Search / Delete

// IO Funcs

// TODO - Input / Output
