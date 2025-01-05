#ifndef UTILS_H
#define UTILS_H

#include "Declarations.h"
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
    void PrintNewlines(const int numLines, std::ostream &os = std::cout);

    std::string TrimString(const std::string& str);
    std::string *TokenizeString(std::string str, const std::string &delimiter, int &tokenCount, const bool useTrim = false);

    bool ParseFile(const std::string &filePath, GridData &gridData, std::string &parseFailReason);
    bool ExtractGridRange(const std::string &rangeLine, GridData &gridData, bool &rangeX, std::string &extractFailReason);
    bool ExtractCityData(const std::string &cityLine, GridData &gridData, std::string &extractFailReason);

    // std::vector<std::string> StrSplit(const std::string &str, const char delimiter);
    // ReadFileStatus ReadLinesFromFile(const std::string &filePath);
    // std::unordered_set<Vec2D, Vec2D::Hash> VectorToSet(const std::vector<Vec2D> &posVec);
    // std::vector<Vec2D> SetToVector(const std::unordered_set<Vec2D, Vec2D::Hash> &posSet);
} // namespace Utils

#endif