#ifndef UTILS_H
#define UTILS_H

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

    bool StrContains(const std::string &str, const char subStr) {
        return str.find(subStr) != std::string::npos;
    }

    bool StrEndsWith(const std::string &str, const std::string &suffix) {
        return str.length() > suffix.length() &&
               str.compare(str.length() - suffix.length(), suffix.length(), suffix);
    }

    template <typename T>
    void PrintVector(const std::vector<T> &vec) {
        for (const auto &val : vec) {
            std::cout << val << " | ";
        }
    }
} // namespace Utils

#endif