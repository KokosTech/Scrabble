#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <fstream>

class UMap
{
private:
    std::unordered_map<int, std::string> map;
    int count;

public:
    UMap();
    UMap(const UMap &other);

    UMap &operator=(const UMap &other);

    ~UMap();

    // Funcs
    void insert(const std::string &word);
    void remove(const int);
    void sort(UMap &other);

    // Getters and setters
    const std::unordered_map<int, std::string> &getMap() const;
    std::vector<std::string> getWords();

    // IO Streams
    friend std::ostream &operator<<(std::ostream &os, const UMap &other);
    friend std::istream &operator>>(std::istream &is, UMap &other);

    // IO Funcs
    void printMap();

    // ToUpperCase , ToLowerCase

    UMap ToUpperCase(UMap &other);
    UMap ToLowerCase(UMap &other);

    // TODO - Write to file
    friend void writeMapToFile(const std::string &filename, UMap &other);
    friend void writeMapToFile(std::ofstream &f, UMap &other);

    // Read from file
    friend void readMapFromFile(const std::string &filename, UMap &other);
    friend void readMapFromFile(std::ifstream &f, UMap &other);
};