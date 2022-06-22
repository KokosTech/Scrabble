#include <exception>

#include "ptrie_node.hpp"
#include "ptrie_edge.hpp"

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
    this->validate(firstCharacter);

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

void TrieNode::removeEdge(char firstCharacter) {
    this->validate(firstCharacter);

    this->children.erase(firstCharacter);
}

// Setters and getters

void TrieNode::setIsEnd(bool isEnd) { this->isEnd = isEnd; }

bool TrieNode::getIsEnd() const { return this->isEnd; }

TrieEdge *TrieNode::getEdge(char firstCharacter) const {
    this->validate(firstCharacter);
    
    if(this->checkIfEdgeExists(firstCharacter)) return this->children.at(firstCharacter);
    return nullptr;
}

//----------------------------------------------------------------

void addEdgeToTrieNode(TrieNode *node, char firstCharacter, const std::string &prefix, bool edgeNodeIsEnd) {
    TrieNode *edgenode = new TrieNode(edgeNodeIsEnd);
    TrieEdge *edge = new TrieEdge(prefix, edgenode);
    node->addEdge(firstCharacter, edge);
} 
