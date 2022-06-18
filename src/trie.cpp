#include <string>
#include <unordered_map>

#define NUM_CHARS 26

class Trie {
private:
    std::unordered_map<char, Trie*> characters;
    bool isEnd;
public:
    Trie() 
    : isEnd(false) 
    {}

    ~Trie() {
        for(auto i: this->characters) {
            delete i.second;
        }
    }

    bool insert(const std::string& word) {
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

    bool search(const std::string& word) {
        Trie *tmp = this;
        const uint length = word.length();
        for(int i = 0; i < length; ++i) {
            if(tmp->characters.find(char(word[i]-97)) == tmp->characters.end()) {
                return false;
            }
            tmp = tmp->characters[char(word[i]-97)];
        }

        if(!tmp->isEnd) 
            return false;

        return true;
    }

    void deleteWord(const std::string& word) {
        Trie* tmp = this;
        const uint length = word.size();

        tmp->isEnd = false;
    }
};