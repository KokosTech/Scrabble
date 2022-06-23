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
                std::string temp = currEdge->getPrefix().substr(currWordPart.length());
                // TrieNode *newnode = new TrieNode(false);
                // TrieEdge *newedge = new TrieEdge(temp, newnode);
                currEdge->setPrefix(currEdge->getPrefix().substr(0, currWordPart.length()));
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

bool PTrie::search(const std::string &word) {
    TrieNode *currNode = this->root;
    unsigned int currIndex = 0;
    TrieEdge *currEdge;
    while(currIndex <= word.length()) {
        currEdge = currNode->getEdge(word[currIndex]);
        std::string currWordPart = word.substr(currIndex);
        if(!currEdge) return false;

        int matchIndex = matchPrefixChars(currEdge->getPrefix(), currWordPart);
        if(matchIndex == ALL_MATCH && currEdge->getPrefix().length() <= currWordPart.length()) {
            currNode = currEdge->getNode();
            currIndex += currEdge->getPrefix().length();
            if(currEdge->getPrefix().length() == currWordPart.length()) {
                break;
            }
        } else {
            return false;
        }                        
    }
    return currNode->getIsEnd();
}

TrieNode* PTrie::_delete_rec(TrieNode *node, TrieEdge *edge, const std::string &word) {
    if(!node) return nullptr;

    if(word.empty()) {
        if(!node->hasEdges() && node != this->root) {
            delete node;
            return nullptr;
        }
        node->setIsEnd(false);

        return node;
    }

    int matchIndex = 0;
    if(edge) matchIndex = matchPrefixChars(edge->getPrefix(), word);
    // std::cout << edge->getPrefix() << " " << word << std::endl;
    if(matchIndex == ALL_MATCH && edge->getPrefix().length() <= word.length()) {
        matchIndex = edge->getPrefix().length();

        std::string nextWordPart = word.substr(matchIndex);
        TrieNode *nextnode = edge->getNode();
        TrieEdge *nextedge = nextnode->getEdge(nextWordPart[0]);

        TrieNode *prevnode = _delete_rec(nextnode, nextedge, nextWordPart); 
        edge->setNode(prevnode);
        if(!prevnode) {
            
            delete edge;
            node->removeEdge(word[0]);
            if(node != this->root && !node->getIsEnd() && !node->hasEdges()) 
            {
                delete node;  
                return nullptr;  
            } 
        } else if(!prevnode->getIsEnd() && prevnode->getEdgeCount() == 1) {

            node->removeEdge(word[0]);
            TrieEdge *prevedge = prevnode->getEdges().begin()->second;
            std::string addprefix = edge->getPrefix() + prevedge->getPrefix();

            addEdgeToTrieNode(node, addprefix[0], addprefix, prevedge->getNode());
            
            prevedge->setNode(nullptr);
            //when the destructor of edge is called the memory for prevnode and prevedge will be freed too
            delete edge;
        }
    } else {
        throw std::invalid_argument("Cannot delete a word that is not in the tree!");
    }
    return node;
}

void PTrie::remove(const std::string &word) {
    if(word.empty()) throw std::invalid_argument("Cannot delete an empty string!");
    this->_delete_rec(this->root, this->root->getEdge(word[0]), word);
}

<<<<<<< Updated upstream
// TODO - Input / Output
=======
// TODO IO Funcs
>>>>>>> Stashed changes
