#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> StrSplit(const std::string &str, const char delimiter) {
        std::vector<std::string> allTokens;
        std::string token;

        for (const char ch : str) {
            if (ch == delimiter) {
                if (!token.empty()) {
                    allTokens.emplace_back(token);
                    token.clear();
                }
            } else {
                token += ch;
            }
        }
        if (!token.empty()) {
            allTokens.emplace_back(token);
        }
        return allTokens;
    }

    bool StrContains(const std::string &str, const std::string &subStr) {
        return str.find(subStr) != std::string::npos;
    }

    // bool StrEndsWith(const std::string &str, const std::string &suffix) {
    //     return str.length() > suffix.length() &&
    //            str.compare(str.length() - suffix.length(), suffix.length(), suffix);
    // }

    // template <typename T>
    // void PrintVector(const std::vector<T> &vec) {
    //     for (const auto &val : vec) {
    //         std::cout << val << " | ";
    //     }
    // }

    void PrintNewlines(const int numLines) {
        for (int i = 0; i < numLines; i++) {
            std::cout << std::endl;
        }
    }

    ReadFileStatus ReadLinesFromFile(const std::string &filePath) {
        std::ifstream inFile(filePath);
        if (!inFile) {
            return ReadFileStatus(false);
        }

        std::vector<std::string> allLines;
        std::string line;
        while (std::getline(inFile, line)) {
            allLines.emplace_back(line);
        }
        inFile.close();
        return ReadFileStatus(true, allLines);
    }
} // namespace Utils

#endif