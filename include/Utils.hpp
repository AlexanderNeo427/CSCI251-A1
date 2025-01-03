#ifndef UTILS_H
#define UTILS_H

#include "Declarations.hpp"

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

namespace Utils {
    template <class T>
    void PaddedPrint(const T val, const int padAmount) {
        std::cout << val;
        for (int i = 0; i < padAmount; i++) {
            std::cout << " ";
        }
    }

    char GetLMH(const float val);
    std::vector<std::string> StrSplit(const std::string &str, const char delimiter);
    bool StrContains(const std::string &str, const std::string &subStr);
    void PrintNewlines(const unsigned short numLines);
    ReadFileStatus ReadLinesFromFile(const std::string &filePath);
    std::unordered_set<Vec2D, Vec2D::Hash> VectorToSet(const std::vector<Vec2D> &posVec);
    std::vector<Vec2D> SetToVector(const std::unordered_set<Vec2D, Vec2D::Hash> &posSet);
} // namespace Utils

#endif