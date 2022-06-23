#include "ptrie_node.hpp"
#include "ptrie_edge.hpp"

#include <iostream>

TrieNode::TrieNode() : isEnd(false) { }

TrieNode::TrieNode(bool isEnd) : isEnd(isEnd) { }

TrieNode::~TrieNode() {
    for(auto i: children)
        delete i.second;
}

// Helpers

void TrieNode::validate(char firstCharacter) const {
    if(firstCharacter < 'A' || firstCharacter > 'Z') throw std::invalid_argument("Character must be from the English alphabet");
}

bool TrieNode::checkIfEdgeExists(char firstCharacter) const {    
    if(this->children.find(firstCharacter) != this->children.end())
        return true;
    return false;
}

// Funcs

void TrieNode::addEdge(char firstCharacter, TrieEdge *edge) {
    this->validate(firstCharacter);

    if(this->checkIfEdgeExists(firstCharacter)) return; 
    this->children[firstCharacter] = edge;
}

void TrieNode::addEdge(const std::string &prefix, TrieNode *node) {
    this->validate(prefix[0]);
    if(this->checkIfEdgeExists(prefix[0])) return;
    TrieEdge *edge = new TrieEdge(prefix, node);
    this->children[prefix[0]] = edge;
}

void TrieNode::removeEdge(char firstCharacter) {
    this->validate(firstCharacter);

    this->children.erase(firstCharacter);
}

bool TrieNode::hasEdges() {
    if(this->children.empty()) return false;
    return true;
}

// Setters and getters

void TrieNode::setIsEnd(bool isEnd) { this->isEnd = isEnd; }

bool TrieNode::getIsEnd() const { return this->isEnd; }

TrieEdge *TrieNode::getEdge(char firstCharacter) const {    
    if(this->checkIfEdgeExists(firstCharacter)) return this->children.at(firstCharacter);
    return nullptr;
}

const std::unordered_map<char, TrieEdge*> &TrieNode::getEdges() const {
    return this->children;
}

unsigned int TrieNode::getEdgeCount() const {
    return this->children.size();
}

//----------------------------------------------------------------

void addEdgeToTrieNode(TrieNode *node, char firstCharacter, const std::string &prefix, bool edgeNodeIsEnd) {
    TrieNode *edgenode = new TrieNode(edgeNodeIsEnd);
    TrieEdge *edge = new TrieEdge(prefix, edgenode);
    node->addEdge(firstCharacter, edge);
} 
