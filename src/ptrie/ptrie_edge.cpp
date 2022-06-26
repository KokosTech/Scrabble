#include "ptrie_edge.hpp"
#include "ptrie_node.hpp"

TrieEdge::TrieEdge(const std::string &prefix) 
: prefix(prefix) {
    TrieNode *node = new TrieNode;
    this->node = node;
}

TrieEdge::TrieEdge(const std::string &prefix, TrieNode *node)
: prefix(prefix), node(node) { }

// TODO - more constructor and optimization

TrieEdge::~TrieEdge() { delete this->node; }

// Setters and getters

void TrieEdge::setPrefix(const std::string &prefix) { this->prefix = prefix; }

void TrieEdge::setNode(TrieNode *node) { this->node = node; }

const std::string &TrieEdge::getPrefix() const { return this->prefix; }

TrieNode *TrieEdge::getNode() const { return this->node; }

