#ifndef UTILS_H
#define UTILS_H

#include "Declarations.h"
#include <fstream>
#include <iostream>

namespace Utils { 
    void PrintNewlines(const int numLines, std::ostream &os = std::cout);
    std::string TrimString(const std::string &str);
    std::string *TokenizeString(std::string str, const std::string &delimiter, int &tokenCount, const bool useTrim = false);

    void AllocateMemory(GridData &gridData);
    void FreeMemory(GridData &gridData);
} // namespace Utils

#endif