#include "umap.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>
#include <vector>

#include <exception>
#include <algorithm>

UMap::UMap() {}

UMap::UMap(const UMap &other)
{
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
    if (this->map.find(word) == this->map.end())
    {
        this->map[word] = 1;
    }
    else
    {
        this->map[word]++;
    }
}

void UMap::remove(const int index)
{
    std::vector<std::string> words = this->getWords();
    if (index >= 0 && index < words.size())
    {
        this->map.erase(words[index]);
    }
}

const std::unordered_map<std::string, int> &UMap::getMap() const
{
    return this->map;
}

std::vector<std::string> UMap::getWords() const
{
    std::vector<std::string> words;
    for (std::pair<std::string, int> pair : this->map)
    {
        words.push_back(pair.first);
    }
    return words;
}

std::ostream &operator<<(std::ostream &os, const UMap &other)
{
    for (std::pair<std::string, int> pair : other.map)
    {
        os << pair.first << ": " << pair.second << std::endl;
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
    for (std::pair<std::string, int> pair : this->map)
    {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

void writeToFile(const std::string &fileName, const UMap &other)
{
    std::ofstream file;
    file.open(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    file << other;
    if (!file.good())
    {
        throw std::runtime_error("Could not write to file");
    }
    file.close();
}

void writeToFile(std::ofstream &file, const UMap &other)
{
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    file << other;
    if (!file.good())
    {
        throw std::runtime_error("Could not write to file");
    }
}

void readFromFile(const std::string &fileName, UMap &other)
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
    file.close();
}

void readFromFile(std::ifstream &file, UMap &other)
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
}