#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>

namespace Utils {
    template <class T>
    void PaddedPrint(const T val, const int padAmount) {
        std::cout << val;
        for (int i = 0; i < padAmount; i++) {
            std::cout << " ";
        }
    }

    char GetLMH(const float val);
    bool StrContains(const std::string &str, const std::string &subStr);
    void PrintNewlines(const unsigned short numLines);
    
    // std::vector<std::string> StrSplit(const std::string &str, const char delimiter);
    // ReadFileStatus ReadLinesFromFile(const std::string &filePath);
    // std::unordered_set<Vec2D, Vec2D::Hash> VectorToSet(const std::vector<Vec2D> &posVec);
    // std::vector<Vec2D> SetToVector(const std::unordered_set<Vec2D, Vec2D::Hash> &posSet);
} // namespace Utils

#endif