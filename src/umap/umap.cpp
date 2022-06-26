#include "umap.hpp"
#include <unordered_map>

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>
#include <unordered_map>

#include <exception>
#include <algorithm>

UMap::UMap() : count(0)
{
}

UMap::UMap(const UMap &other)
{
    this->count = other.count;
    this->map = other.map;
}

UMap &UMap::operator=(const UMap &other)
{
    if (this != &other)
    {
        this->map = other.map;
    }
    return *this;
}

UMap::~UMap() {}

void UMap::insert(const std::string &word)
{
    this->map[this->count++] = word;
}

void UMap::remove(const int index)
{
    std::vector<std::string> words = this->getWords();
    if (index >= 0 && index < words.size())
    {
        this->map.erase(index);
    }
}

void UMap::sort(UMap &other)
{
    std::vector<std::string> words = other.getWords();
    std::sort(words.begin(), words.end());
    other.map.clear();
    for (int i = 0; i < words.size(); i++)
    {
        other.map[i] = words[i];
    }
}

const std::unordered_map<int, std::string> &UMap::getMap() const
{
    return this->map;
}

std::vector<std::string> UMap::getWords()
{
    std::vector<std::string> words;
    for (std::pair<int, std::string> pair : this->map)
    {
        words.push_back(pair.second);
    }
    return words;
}

std::ostream &operator<<(std::ostream &os, const UMap &other)
{
    for (std::pair<int, std::string> pair : other.map)
    {
        os << pair.second << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, UMap &other)
{
    std::string line;
    while (std::getline(is, line))
    {
        std::stringstream ss(line);
        std::string word;
        int count;
        ss >> word >> count;
        other.insert(word);
    }
    return is;
}

void UMap::printMap()
{
    for (std::pair<int, std::string> pair : this->map)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

UMap UMap::ToUpperCase(UMap &other)
{
    UMap newMap;
    for (std::pair<int, std::string> pair : other.map)
    {
        for (int i = 0; i < pair.second.length(); i++)
        {
            pair.second[i] = toupper(pair.second[i]);
        }
        newMap.insert(pair.second);
    }
    return newMap;
}

UMap UMap::ToLowerCase(UMap &other)
{
    UMap newMap;
    for (std::pair<int, std::string> pair : other.map)
    {
        for (int i = 0; i < pair.second.length(); i++)
        {
            pair.second[i] = tolower(pair.second[i]);
        }
        newMap.insert(pair.second);
    }
    return newMap;
}

void writeMapToFile(const std::string &fileName, UMap &other)
{
    std::ofstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    other.ToLowerCase(other);
    file << other;
    if (!file.good())
    {
        throw std::runtime_error("Could not write to file");
    }
    file.close();
}

void writeMapToFile(std::ofstream &file, UMap &other)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    other.ToLowerCase(other);
    file << other;
    if (!file.good())
    {
        throw std::runtime_error("Could not write to file");
    }
}

void readMapFromFile(const std::string &fileName, UMap &other)
{
    std::ifstream file;
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    file.open(fileName);
    file >> other;
    if (!file.good())
    {
        throw std::runtime_error("Could not read from file");
    }
    other.ToUpperCase(other);
    file.close();
}

void readMapFromFile(std::ifstream &file, UMap &other)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    file >> other;
    if (!file.good())
    {
        throw std::runtime_error("Could not read from file");
    }
    other.ToUpperCase(other);
}
