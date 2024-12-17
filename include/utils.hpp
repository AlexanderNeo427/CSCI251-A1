#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace Utils {
    template <typename T>
    void PaddedPrint(const T val) {
        std::cout << val;
        for (int i = 0; i < 2; i++) {
            std::cout << " ";
        }
    }

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