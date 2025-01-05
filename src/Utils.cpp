#include "Utils.h"
#include <sstream>

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

void Utils::PrintNewlines(const int numLines, std::ostream &os) {
    for (int i = 0; i < numLines; i++) {
        os << std::endl;
    }
}

std::string Utils::TrimString(const std::string &str) {
    std::size_t start = str.find_first_not_of(" \t\n\r");
    std::size_t end = str.find_last_not_of(" \t\n\r");
    if (start == std::string::npos) {
        return "";
    }
    const std::string trimmmedStr = str.substr(start, end - start + 1);
    return trimmmedStr;
}

std::string *Utils::TokenizeString(std::string str, const std::string &delimiter, int &tokenCount, const bool useTrim) {
    // Count number of tokens
    std::string strCopy = str;
    std::size_t pos = 0;
    tokenCount = 0;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        tokenCount++;
        str.erase(0, pos + delimiter.length());
    }
    tokenCount++; // Last token

    std::string *allTokens = new std::string[tokenCount];
    std::size_t index = 0;
    str = strCopy; // Reset string

    while ((pos = str.find(delimiter)) != std::string::npos) {
        std::string newToken = useTrim ? Utils::TrimString(str.substr(0, pos)) : str.substr(0, pos);
        allTokens[index++] = newToken;
        str.erase(0, pos + delimiter.length());
    }
    allTokens[index] = str; // Last token
    return allTokens;
}

bool Utils::ParseFile(const std::string &filePath, GridData &gridData, std::string &parseFailReason) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        parseFailReason = "Error while trying to open file at: " + filePath;
        return false;
    }

    bool rangeXInitialized = false, rangeYInitialized = false;
    bool cityInitialized = false, cloudInitialized = false, pressureInitialized = false;

    std::string aLine;
    while (std::getline(inFile, aLine)) {
        if (aLine.find("Grid") != std::string::npos) {
            std::string extractFailReason = "";
            const bool extractSuccess = Utils::ExtractCityData(aLine, gridData, extractFailReason);
            if (!extractSuccess) {
                parseFailReason = extractFailReason;
                return false;
            }

        } else if (aLine.find("citylocation.txt")) {
            std::string extractFailReason = "";
            const bool extractSuccess = Utils::ExtractCityData(aLine, gridData, extractFailReason);
            if (!extractSuccess) {
                parseFailReason = extractFailReason;
                return false;
            }
        } else if (aLine.find("cloudcover.txt")) {
        } else if (aLine.find("pressure.txt")) {
        }
    }

    if (rangeXInitialized && rangeYInitialized && cityInitialized &&
        cloudInitialized && pressureInitialized) {
        gridData.isDataInitialized = true;
    }
    inFile.close();
    return true;
}

bool Utils::ExtractGridRange(const std::string &rangeLine, GridData &gridData, bool &rangeX, std::string &extractFailReason) {
    // TODO: Stuff
    return true;
}

bool Utils::ExtractCityData(const std::string &cityLine, GridData &gridData, std::string &extractFailReason) {
    // Tokenize string - check correct number of tokens
    int tokenCount = 0;
    std::string *const allTokens = Utils::TokenizeString(cityLine, "-", tokenCount);
    if (tokenCount != 3) {
        std::ostringstream oss;
        oss << "=== Extracting city data failure ===" << std::endl;
        oss << "Following line doesnt adhere to format: " << std::endl;
        oss << cityLine << std::endl;
        extractFailReason = oss.str();
        return false;
    }

    int coordX = 0, coordY = 0;
    { // Try to extract the x and y from the location string
        int coordCount = 0;
        std::string *const coordTokens = Utils::TokenizeString(allTokens[0], ",", tokenCount, true);

        // E.g
        // [0] = "[0"
        // [1] = "8]"
        if (coordCount != 2) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following part of the city data line doesn't adhere to format: " << allTokens[0] << std::endl;
            extractFailReason = oss.str();
            delete coordTokens;
            return false;
        }

        // The coord tokens should start and end with '[' and ']' respectively
        std::string strCoordX = coordTokens[0], strCoordY = coordTokens[1];
        if (strCoordX[0] != '[' || strCoordY[strCoordY.length() - 1] != ']') {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following part of the city data line doesn't adhere to format: " << allTokens[0] << std::endl;
            extractFailReason = oss.str();
            delete coordTokens;
            return false;
        }

        // Actual extraction of the coordX and coordY from the string
        try {
            strCoordX.erase(0, 1);
            strCoordY.pop_back();
            coordX = std::stoi(strCoordX);
            coordY = std::stoi(strCoordY);
        } catch (const std::exception &e) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << e.what() << std::endl;
            extractFailReason = oss.str();
            return false;
        }

        // CoordX and CoordY extracted - check if they are out of bounds
        // NOTE: This part of the code assumes that the gridData.bottomLeft and gridData.topRight is already initialized
        if (coordX < gridData.bottomLeft.x || coordX > gridData.topRight.x ||
            coordY < gridData.bottomLeft.y || coordY > gridData.topRight.y) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Coordinates from the following line are out of range: " << cityLine << std::endl;
            oss << "Actual range X: " << gridData.bottomLeft.x << ", " << gridData.topRight.x << std::endl;
            oss << "Actual range Y: " << gridData.bottomLeft.y << ", " << gridData.topRight.y << std::endl;
            extractFailReason = oss.str();
            return false;
        }
    }

    // Try to extract the city ID and name, and save it
    int cityID = 0;
    try {
        // As it was unspecified, I'm only going to allow city ID's within the range of 0 to 9
        // Because higher ID's mess with the grid rendering
        cityID = std::stoi(allTokens[1]);
        if (cityID < 0 || cityID > MAX_CITY_ID) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following line in file clashes with data saved from previous line:" << std::endl;
            oss << cityLine;
            PrintNewlines(2, oss);
            extractFailReason = oss.str();
            return false;
        }

        // Check for conflicts
        //
        // If the new 'city name' associated with a 'city ID' clashes
        // with what currently exists in the 'cityNames' array/map
        const std::string newCityName = allTokens[2];
        const std::string currCityName = gridData.cityNames[cityID];
        if (!currCityName.empty() && currCityName != newCityName) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following line in file clashes with data saved from previous line: " << std::endl;
            oss << cityLine;
            PrintNewlines(2, oss);
            extractFailReason = oss.str();
            return false;
        }
    } catch (const std::exception &e) {
        std::ostringstream oss;
        oss << "=== Extracting city data failure ===" << std::endl;
        oss << e.what() << std::endl;
        extractFailReason = oss.str();
        return false;
    }

    // The actual saving of the data into the "gridData" reference
    gridData.cityGrid[coordX][coordY] = cityID;
    return true;
}