#include "trie.hpp"

Trie::Trie() 
: isEnd(false)
{}

Trie::~Trie() {
    for(auto i: this->characters) {
        delete i.second;
    }
}

bool Trie::checkString(const std::string& word) {
    for(auto i: word) {
        if(isupper(i) && i != word[0]) return false;
        if(!isalpha(i)) return false;
    }
    return true;
}

bool Trie::insert(const std::string& word) {
    Trie *tmp = this;
    const uint length = word.length();

    if(!checkString(word)) return false;

    for(int i = 0; i < length; ++i) {
        if(tmp->characters.find(word[i]) == tmp->characters.end()) {
            tmp->characters[word[i]] = new Trie();
        }
            
        tmp = tmp->characters[word[i]];
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


std::ostream& operator<<(std::ostream& os, const Trie& other) {

}

void Trie::remove(const std::string& word) {
    
}