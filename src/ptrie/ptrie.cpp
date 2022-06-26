#include "ptrie.hpp"
#include "ptrie_edge.hpp"
#include "ptrie_node.hpp"

#include <iostream>
#include <sstream>  
#include <fstream>

#include <string>
#include <vector>

#include <exception>
#include <algorithm>

PTrie::PTrie() { this->root = new TrieNode(); }

void PTrie::_copyConstructor(TrieNode *thisRoot, TrieNode *otherRoot) {
    if(!otherRoot) return;
    
    for(std::pair<char, TrieEdge*> edges: otherRoot->getEdges()) {
        TrieEdge *otherEdge = edges.second;
        TrieNode *newNode = new TrieNode(otherEdge->getNode()->getIsEnd());
        
        thisRoot->addEdge(otherEdge->getPrefix(), newNode);

        _copyConstructor(newNode, otherEdge->getNode());
    }
}

PTrie::PTrie(const PTrie &other) {
    this->root = new TrieNode();
    _copyConstructor(this->root, other.root);
}

PTrie &PTrie::operator=(const PTrie &other) {  
    if(this != &other) {
        for(std::pair<char, TrieEdge*> edge: this->root->getEdges()) {
            delete edge.second;
        }
        _copyConstructor(this->root, other.root);
    }

    return *this;
}

PTrie::~PTrie() { delete this->root; }

// Helpers

int PTrie::matchPrefixChars(const std::string &prefix, const std::string &word) const {
    for(unsigned int i = 0; i < prefix.length() && i < word.length(); ++i)
        if(word[i] != prefix[i]) return i;
    
    return ALL_MATCH;
}

// Funcs

void PTrie::_insert(TrieNode *current, const std::string &word) {
    if(!current) return;
    if(current->getEdge(word[0]) == nullptr) {
        addEdgeToTrieNode(current, word[0], word, true);
        return;
    }

    TrieEdge *edge = current->getEdge(word[0]);
    std::string prefix = edge->getPrefix();
    int match = matchPrefixChars(prefix, word);

    if(match == -1) {
        if(word.length() == prefix.length()) {
            edge->getNode()->setIsEnd(true);
        } else if (word.length() > prefix.length()) {
            match = prefix.length();
        } else {
            std::string newpref = prefix.substr(word.length());
            TrieEdge *newedge = new TrieEdge(prefix.substr(0, word.length()));
            TrieNode *newnode = new TrieNode(true);

            newedge->setNode(newnode);
            newnode->addEdge(newpref[0], edge);
            edge->setPrefix(newpref);
            current->changeEdge(prefix[0], newedge);
            return;
        }
    } else {
        std::string newpref = prefix.substr(match);
        TrieEdge *newedge = new TrieEdge(prefix.substr(0, match));
        TrieNode *newnode = new TrieNode(false);
        
        newedge->setNode(newnode);
        newnode->addEdge(newpref[0], edge);
        edge->setPrefix(prefix.substr(match));
        current->changeEdge(prefix[0], newedge);
    }

    _insert(current->getEdge(word[0])->getNode(), word.substr(match));
}

void PTrie::insert(const std::string &word) {
    TrieNode *current = this->root;
    _insert(this->root, word);
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
            delete currNode;
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

// Getters and setters

const TrieNode &PTrie::getRoot() const { return *(this->root); }

void PTrie::_getWordRec(TrieNode *root, const std::string &prefix, std::vector<std::string> &words) const {
    if(!root) return;

    if(root->getIsEnd()) words.push_back(prefix);

    std::string currPrefix;

    for(std::pair<char, TrieEdge*> edges: root->getEdges()) {
        TrieEdge *edge = edges.second;
        currPrefix = prefix + edge->getPrefix();
        _getWordRec(edge->getNode(), currPrefix, words);
    }
} 

std::vector<std::string> PTrie::getWords() const {
    std::vector<std::string> words;
    _getWordRec(this->root, "", words);
    return words;
}

// TODO - Input / Output

std::ostream& operator<<(std::ostream& os, const PTrie &other) {
    for (auto i: other.getWords())
        os << i << ' ';

    return os;
}

std::istream& operator>>(std::istream& is, PTrie &other) {
    std::string line;
    while(std::getline(is, line)) {
        if(line.empty()) break;
        std::stringstream ss(line);
        std::string word;
        while(ss >> word) {
            std::transform(word.begin(), word.end(), word.begin(), ::toupper);
            other.insert(word);
        }
    }
    return is;
}

// TODO IO Funcs

void PTrie::print() {
    std::cout << *this;
}

// Write to file

void writeToFile(const std::string &filename, PTrie &other) {
    std::ofstream f;
    if(!f.is_open()) throw std::runtime_error("Cannot write to file");
    f << other;
    if(!f.good()) throw std::runtime_error("Cannot write to file");
    f.close();
}

void writeToFile(std::ofstream &f, const PTrie &other) {
    if(!f.is_open()) throw std::runtime_error("Cannot write to file");
    f << other;
    if(!f.good()) throw std::runtime_error("Cannot write to file");
}

// Read from file

void readFromFile(const std::string &filename, PTrie &other) {
    std::ifstream f;
    f.open(filename, std::ios::in);
    if(!f.is_open()) throw std::runtime_error("Cannot read from file");
    f >> other;
    //if(!f.good()) throw std::runtime_error("Cannot read to file");
    f.close();
}

void readFromFile(std::ifstream &f, PTrie &other) {
    if(!f.is_open() || !f.good()) throw std::runtime_error("Cannot read from file");
    f >> other;
    //if(!f.good()) throw std::runtime_error("Cannot read to file");
}
