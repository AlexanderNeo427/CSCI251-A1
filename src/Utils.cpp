#include "Utils.h"
#include <sstream>

void Utils::PrintNewlines(const int numLines, std::ostream &os) {
    for (int i = 0; i < numLines; i++) {
        os << std::endl;
    }
}

std::string Utils::TrimString(const std::string &str) {
    const std::size_t startPos = str.find_first_not_of(" \t\n\r");
    if (startPos == std::string::npos) {
        return "";
    }
    const std::size_t endPos = str.find_last_not_of(" \t\n\r");
    return str.substr(startPos, endPos - startPos + 1);
}

std::string *Utils::TokenizeString(std::string str, const std::string &delimiter, int &tokenCount, const bool useTrim) {
    // Count number of tokens
    const std::string copyOfOriginalStr = str;
    std::size_t pos = 0;
    tokenCount = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        tokenCount++;
        str.erase(0, pos + delimiter.length());
    }
    tokenCount++; // Last token

    std::string *allTokens = new std::string[tokenCount];
    std::size_t index = 0;
    str = copyOfOriginalStr; // Reset string

    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string newToken = useTrim ? Utils::TrimString(str.substr(0, pos)) : str.substr(0, pos);
        allTokens[index++] = newToken;
        str.erase(0, pos + delimiter.length());
    }
    allTokens[index] = useTrim ? Utils::TrimString(str) : str; // Last token
    return allTokens;
}
