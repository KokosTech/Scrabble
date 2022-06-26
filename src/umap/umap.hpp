#pragma once

#include <string>
#include <vector>

#include "hmap.hpp"

#include <fstream>

class UMap
{
private:
    Map map;

public:
    UMap();
    UMap(const UMap &other);

    UMap &operator=(const UMap &other);

    ~UMap();

    // Funcs
    void insert(const std::string &word);
    void remove(const int);

    // Getters and setters
    const Map &getMap() const;
    std::vector<std::string> getWords() const;

    // IO Streams
    friend std::ostream &operator<<(std::ostream &os, const UMap &other);
    friend std::istream &operator>>(std::istream &is, UMap &other);

    // IO Funcs
    void printMap();

    // ToUpperCase , ToLowerCase

    UMap ToUpperCase(UMap &other);
    UMap ToLowerCase(UMap &other);

    // TODO - Write to file
    friend void writeToFile(const std::string &filename, UMap &other);
    friend void writeToFile(std::ofstream &f, UMap &other);

    // Read from file
    friend void readFromFile(const std::string &filename, UMap &other);
    friend void readFromFile(std::ifstream &f, UMap &other);
};