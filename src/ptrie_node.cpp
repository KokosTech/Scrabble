#include "ptrie_node.hpp"
#include "ptrie_edge.hpp"

TrieNode::TrieNode() 
:isEnd(false)
{}

TrieNode::TrieNode(bool isEnd) 
:isEnd(isEnd)
{}

TrieNode::~TrieNode() {
    for(auto i: children)
        delete i.second;
}

void TrieNode::setIsEnd(bool isEnd) {
    this->isEnd = isEnd;
}

bool TrieNode::checkIfEdgeExists(char firstCharacter) const {
    if(this->children.find(firstCharacter) != this->children.end())
        return true;
    return false;
}

void TrieNode::addEdge(char firstCharacter, TrieEdge *edge) {
    if(this->checkIfEdgeExists(firstCharacter)) return; 
    this->children[firstCharacter] = edge;
}

void TrieNode::removeEdge(char firstCharacter) {
    this->children.erase(firstCharacter);
}

TrieEdge *TrieNode::getEdge(char firstCharacter) const {
    if(this->checkIfEdgeExists(firstCharacter)) return this->children.at(firstCharacter);
    return nullptr;
}

bool TrieNode::getIsEnd() const {
    return this->isEnd;
}
