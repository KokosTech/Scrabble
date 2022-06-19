#include "trie.hpp"

Trie::Trie() 
: isEnd(false)
{}

Trie::~Trie() {
    for(auto i: this->characters) {
        delete i.second;
    }
}

bool Trie::insert(const std::string& word) {
    Trie *tmp = this;
    const uint length = word.length();

    for(int i = 0; i < length; ++i) {
        if(tmp->characters.find(char(word[i]-97)) == tmp->characters.end()) {
            tmp->characters[char(word[i]-97)] = new Trie();
        }
            
        tmp = tmp->characters[char(word[i]-97)];
    }

    if(tmp->isEnd) {
        return false;
    } else {
        tmp->isEnd = true;
    }

    return true;
}

bool Trie::search(const std::string& word) {
    Trie *tmp = this;
    const uint length = word.length();

    for(int i = 0; i < length; ++i) { 
        if(tmp->characters.find(word[i]) == tmp->characters.end()) {
            return false;
        }

        tmp = tmp->characters[word[i]];
    }

    if(tmp->isEnd == false)
        return false;
    
    return true;
}

void Trie::remove(const std::string& word) {

}