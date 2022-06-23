#include "ptrie.hpp"
#include "ptrie_edge.hpp"
#include "ptrie_node.hpp"

#include <iostream>
#include <string>
#include <sstream>  
#include <fstream>
#include <exception>

PTrie::PTrie() { this->root = new TrieNode(); }

PTrie::~PTrie() { delete this->root; }

// Helpers

int PTrie::matchPrefixChars(const std::string &prefix, const std::string &word) const {
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

bool PTrie::search(const std::string &word) const {
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

TrieNode* PTrie::_delete_rec(TrieNode *currNode, const std::string &word) {
    if(!currNode) return nullptr;

    if(word.empty() && currNode->getIsEnd()) {
        if(this->root != currNode && !currNode->hasEdges()) {
            delete currNode;
            return nullptr;
        }
        currNode->setIsEnd(false);
        return currNode;
    }

    TrieEdge *currEdge = currNode->getEdge(word[0]);    
    std::string prefix = currEdge->getPrefix();

    if(!currEdge || (word.rfind(prefix, 0) != 0)) 
        throw std::invalid_argument("Cannot delete word that is not in the dictionary!");

    TrieNode *removed = _delete_rec(currEdge->getNode(), word.substr(prefix.length()));

    currEdge->setNode(removed);
    if(removed == nullptr) {
        delete currEdge;
        currNode->removeEdge(word[0]);

        if(!currNode->hasEdges() && 
           !currNode->getIsEnd() &&
           currNode != this->root) 
        {
            delete currEdge;
            return nullptr;
        }
    } else if(removed->getEdgeCount() == 1 && !removed->getIsEnd()) {
        TrieEdge *reEdge = removed->getEdges().begin()->second;
        currNode->removeEdge(word[0]);

        std::string reString = reEdge->getPrefix();
        std::string currString = currEdge->getPrefix();

        reEdge->setPrefix(currString + reString);
        currNode->addEdge(currString[0], reEdge);

        removed->removeEdge(reString[0]);
        delete currEdge; 
    }

    return currNode;
}

void PTrie::remove(const std::string &word) {
    if(word.empty()) throw std::invalid_argument("Cannot delete an empty string!");
    this->_delete_rec(this->root, word);
}

// TODO - Input / Output

std::ostream& operator<<(std::ostream& os, const PTrie &other) {
    os << "PTrie: " << std::endl;
    os << "Root: " << std::endl;
    os << *other.root << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, PTrie &other) {
    std::string line;
    while(std::getline(is, line)) {
        if(line.empty()) break;
        std::stringstream ss(line);
        std::string word;
        while(ss >> word) {
            other.insert(word);
        }
    }
    return is;
}

// TODO IO Funcs

void PTrie::print(std::ostream &os) {
    os << *this;
}

// TODO - Write to file

void writeToFile(const PTrie &other) {

}

void writeToFile(const std::string &filename, const PTrie &other) {

}

void writeToFile(std::ofstream &f, const PTrie &other) {

}

// TODO - Read from file

void readFromFile(PTrie &other) {

}

void readFromFile(const std::string &filename, PTrie &other) {

}

void readFromFile(std::ifstream &fv, PTrie &other) {

}
