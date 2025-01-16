#include "Utils.h"
#include <algorithm>
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

    std::string *const allTokens = new std::string[tokenCount];
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

std::string Utils::ToLower(std::string str) {
    std::transform(
        str.begin(), str.end(), str.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });
    return str;
}

void Utils::AllocateMemory(GridData &gridData) {
    const int rangeX = (gridData.topRight.x - gridData.bottomLeft.x) + 1;
    const int rangeY = (gridData.topRight.y - gridData.bottomLeft.y) + 1;

    gridData.cityGrid = new int *[rangeX];
    gridData.cloudGrid = new int *[rangeX];
    gridData.pressureGrid = new int *[rangeX];

    for (int x = 0; x < rangeX; x++) {
        gridData.cityGrid[x] = new int[rangeY];
        gridData.cloudGrid[x] = new int[rangeY];
        gridData.pressureGrid[x] = new int[rangeY];

        for (int y = 0; y < rangeY; y++) {
            gridData.cityGrid[x][y] = 0;
            gridData.cloudGrid[x][y] = 0;
            gridData.pressureGrid[x][y] = 0;
        }
    }
}

void Utils::FreeMemory(GridData &gridData) {
    const int rangeX = (gridData.topRight.x - gridData.bottomLeft.x) + 1;
    for (int x = 0; x < rangeX; x++) {
        delete[] gridData.cityGrid[x];
        delete[] gridData.cloudGrid[x];
        delete[] gridData.pressureGrid[x];
        gridData.cityGrid[x] = nullptr;
        gridData.cloudGrid[x] = nullptr;
        gridData.pressureGrid[x] = nullptr;
    }
    delete[] gridData.cityGrid;
    delete[] gridData.cloudGrid;
    delete[] gridData.pressureGrid;
    gridData.cityGrid = nullptr;
    gridData.cloudGrid = nullptr;
    gridData.pressureGrid = nullptr;
}