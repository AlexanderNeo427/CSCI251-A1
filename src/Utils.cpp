#include "Utils.hpp"

char Utils::GetLMH(const float val) {
    if (val >= 0 && val < 35) {
        return 'L';
    } else if (val >= 35 && val < 65) {
        return 'M';
    } else if (val >= 65 && val < 100) {
        return 'H';
    }
    return '-';
}

std::vector<std::string> Utils::StrSplit(const std::string &str, const char delimiter) {
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

bool Utils::StrContains(const std::string &str, const std::string &subStr) {
    return str.find(subStr) != std::string::npos;
}

void Utils::PrintNewlines(const unsigned short numLines) {
    for (unsigned short i = 0; i < numLines; i++) {
        std::cout << std::endl;
    }
}

ReadFileStatus Utils::ReadLinesFromFile(const std::string &filePath) {
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

std::unordered_set<Vec2D, Vec2D::Hash> Utils::VectorToSet(const std::vector<Vec2D> &posVec) {
    std::unordered_set<Vec2D, Vec2D::Hash> posSet({});
    for (const Vec2D &pos : posVec) {
        posSet.insert(pos);
    }
    return posSet;
}

std::vector<Vec2D> Utils::SetToVector(const std::unordered_set<Vec2D, Vec2D::Hash> &posSet) {
    std::vector<Vec2D> posVec;
    for (const Vec2D &pos : posSet) {
        posVec.emplace_back(pos);
    }
    return posVec;
}
