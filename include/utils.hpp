#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> strSplit(const std::string &str, const char delimiter) {
        std::vector<std::string> tokens;
        
        return tokens;
    }

    bool strContains(const std::string &str, const char subStr) {
        return str.find(subStr) != std::string::npos;
    }

    bool strEndsWith(const std::string &str, const std::string &suffix) {
        return str.length() > suffix.length() &&
               str.compare(str.length() - suffix.length(), suffix.length(), suffix);
    }
} // namespace Utils

#endif