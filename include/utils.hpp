#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> splitString(const std::string &str, const char delimiter) {
        std::vector<std::string> tokens;
        return tokens;
    }

    bool stringContains(const std::string &str, const char subStr) {
        return str.find(subStr) != std::string::npos;
    }
} // namespace Utils

#endif