#ifndef UTILS_H
#define UTILS_H

#include "Declarations.h"
#include <fstream>
#include <iostream>

namespace Utils {
    // template <class T>
    // void PaddedPrint(const T val, const int padAmount) {
    //     std::cout << val;
    //     for (int i = 0; i < padAmount; i++) {
    //         std::cout << " ";
    //     }
    // }
    char GetLMH(const float val);
    void PrintNewlines(const int numLines, std::ostream &os = std::cout);
    std::string TrimString(const std::string &str);
    std::string *TokenizeString(std::string str, const std::string &delimiter, int &tokenCount, const bool useTrim = false);
    void ReclaimMemory(GridData& gridData);
} // namespace Utils

#endif