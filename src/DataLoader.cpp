#include "DataLoader.h"
#include "Utils.h"
#include <sstream>

bool DataLoader::ParseFile(const std::string &filePath, GridData &gridData, std::string &parseFailReason) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        parseFailReason = "Error while trying to open file at: " + filePath;
        return false;
    }

    GridData newGridData;

    // The current 'valid line' number.
    // Empty lines and comments "//" do not count as valid lines
    int currentValidLineNo = 0;

    bool rangeXInitialized = false, rangeYInitialized = false, arraysInitialized = false;
    bool cityInitialized = false, cloudInitialized = false, pressureInitialized = false;

    std::string aLine;
    while (std::getline(inFile, aLine)) {

        // Once we have extracted the "X" and "Y" minmax range, but have yet to initialize the arrays...
        // Init the arrays here
        if (rangeXInitialized && rangeYInitialized && !arraysInitialized) {
            Utils::AllocateMemory(newGridData);
            arraysInitialized = true;
            Utils::PrintNewlines(1);
            std::cout << "Storing data from input file: " << std::endl;
        }

        if (aLine.empty() || aLine.find("//") == 0) { // Ignore empty lines and comments
            continue;
        } else {
            currentValidLineNo++;
        }
        // std::cout << "Current Line: " << currentValidLineNo << std::endl;
        // std::cout << "Line: " << aLine;
        // Utils::PrintNewlines(2);

        if (currentValidLineNo == 1 || currentValidLineNo == 2) {
            std::string extractFailReason = "";
            bool isRangeX;

            const bool extractSuccess = DataLoader::ExtractGridRange(aLine, newGridData, isRangeX, extractFailReason);
            if (!extractSuccess) {
                parseFailReason = extractFailReason;
                if (arraysInitialized) {
                    Utils::FreeMemory(newGridData);
                }
                return false;
            }

            if (isRangeX) {
                rangeXInitialized = true;
            } else {
                rangeYInitialized = true;
            }
        } else if (currentValidLineNo == 3) {
            std::string readFailReason = "";
            const bool readSuccess = DataLoader::ReadCityTextFile(aLine, newGridData, readFailReason);
            if (!readSuccess) {
                parseFailReason = readFailReason;
                if (arraysInitialized) {
                    Utils::FreeMemory(newGridData);
                }
                return false;
            }
            cityInitialized = true;
            std::cout << aLine << ".... done!" << std::endl;
        } else if (currentValidLineNo == 4) {
            std::string readFailReason = "";
            const bool readSuccess = DataLoader::ReadGenericTextFile(aLine, newGridData, readFailReason, true);
            if (!readSuccess) {
                parseFailReason = readFailReason;
                if (arraysInitialized) {
                    Utils::FreeMemory(newGridData);
                }
                return false;
            }
            cloudInitialized = true;
            std::cout << aLine << ".... done!" << std::endl;
        } else if (currentValidLineNo == 5) {
            std::string readFailReason = "";
            const bool readSuccess = DataLoader::ReadGenericTextFile(aLine, newGridData, readFailReason, false);
            if (!readSuccess) {
                parseFailReason = readFailReason;
                if (arraysInitialized) {
                    Utils::FreeMemory(newGridData);
                }
                return false;
            }
            pressureInitialized = true;
            std::cout << aLine << ".... done!" << std::endl;
        }
    }

    if (!rangeXInitialized || !rangeYInitialized || !arraysInitialized ||
        !cityInitialized || !cloudInitialized || !pressureInitialized) {
        std::cerr << "Something is not initialized properly..." << std::endl;
        if (arraysInitialized) {
            Utils::FreeMemory(newGridData);
        }
        return false;
    }

    if (gridData.isDataLoaded) {
        Utils::FreeMemory(gridData);
    }
    gridData = newGridData;
    gridData.isDataLoaded = true;
    inFile.close();
    return true;
}

bool DataLoader::ExtractGridRange(const std::string &rangeLine, GridData &gridData, bool &isRangeX, std::string &extractFailReason) {
    // Validate number of tokens
    // [0] - GridX_IdxRange | [1] - 0-8
    int tokenCount = 0;
    std::string *allTokens = Utils::TokenizeString(rangeLine, "=", tokenCount);
    if (tokenCount != 2) {
        std::ostringstream oss;
        oss << "=== Extract Grid Range Error ===" << std::endl;
        oss << "Line is in wrong format: " << rangeLine << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    // Validate information before "="
    const std::string beforeEquals = allTokens[0];
    if (beforeEquals == "GridX_IdxRange") {
        isRangeX = true;
    } else if (beforeEquals == "GridY_IdxRange") {
        isRangeX = false;
    } else {
        std::ostringstream oss;
        oss << "=== Extract Grid Range Error ===" << std::endl;
        oss << "Line is in wrong format: " << beforeEquals << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    // Validate number of "range" tokens
    // [0] - 0 | [1] - 8
    const std::string afterEquals = allTokens[1];
    int rangeTokenCount = 0;
    std::string *rangeTokens = Utils::TokenizeString(afterEquals, "-", rangeTokenCount);
    if (rangeTokenCount != 2) {
        std::ostringstream oss;
        oss << "=== Extract Grid Range Error ===" << std::endl;
        oss << "Line is in wrong format: " << afterEquals << std::endl;
        extractFailReason = oss.str();

        delete[] rangeTokens;
        delete[] allTokens;
        rangeTokens = nullptr;
        allTokens = nullptr;
        return false;
    }

    // Extract int from the 'minmaxTokens' string
    int min = 0, max = 0;
    try {
        min = std::stoi(rangeTokens[0]);
        max = std::stoi(rangeTokens[1]);
    } catch (const std::exception &e) {
        std::ostringstream oss;
        oss << "=== Extract Grid Range Error ===" << std::endl;
        oss << "Line is in wrong format: " << afterEquals << std::endl;
        extractFailReason = oss.str();

        delete[] rangeTokens;
        delete[] allTokens;
        rangeTokens = nullptr;
        allTokens = nullptr;
        return false;
    }

    if (max < min) {
        std::ostringstream oss;
        oss << "=== Extract Grid Range Error ===" << std::endl;
        oss << "Max is smaller than min in line: " << rangeLine << std::endl;
        extractFailReason = oss.str();

        delete[] rangeTokens;
        delete[] allTokens;
        rangeTokens = nullptr;
        allTokens = nullptr;
        return false;
    }

    // int of min and max have been extracted - save to gridData
    if (isRangeX) {
        gridData.bottomLeft.x = min;
        gridData.topRight.x = max;
        std::cout << "Reading in GridX_IdxRange: " << min << "-" << max << "... done!" << std::endl;
    } else {
        gridData.bottomLeft.y = min;
        gridData.topRight.y = max;
        std::cout << "Reading in GridY_IdxRange: " << min << "-" << max << "... done!" << std::endl;
    }
    delete[] rangeTokens;
    delete[] allTokens;
    rangeTokens = nullptr;
    allTokens = nullptr;
    return true;
}

bool DataLoader::ReadCityTextFile(const std::string &filePath, GridData &gridData, std::string &readFailReason) {
    std::ifstream cityDataFile(filePath);
    if (!cityDataFile.is_open()) {
        readFailReason = "Failed to open file: " + filePath;
        return false;
    }

    std::string aLine;
    while (std::getline(cityDataFile, aLine)) {
        if (aLine.empty()) {
            continue;
        }
        std::string extractFailReason = "";
        const bool extractSuccess = DataLoader::ExtractCityDataLine(aLine, gridData, extractFailReason);
        if (!extractSuccess) {
            readFailReason = extractFailReason;
            return false;
        }
    }
    return true;
}

bool DataLoader::ExtractCityDataLine(const std::string &cityLine, GridData &gridData, std::string &extractFailReason) {
    // Tokenize string - check correct number of tokens
    int tokenCount = 0;
    std::string *allTokens = Utils::TokenizeString(cityLine, "-", tokenCount);
    if (tokenCount != 3) {
        std::ostringstream oss;
        oss << "=== Extracting city data failure ===" << std::endl;
        oss << "Following line has wrong token count (needs to be 3): " << cityLine << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    // Try to extract the x and y coordinates from the string
    int xCoord = 0, yCoord = 0;
    {
        int coordCount = 0;
        std::string *coordTokens = Utils::TokenizeString(allTokens[0], ",", coordCount, true);

        // E.g
        // [0] = "[0"
        // [1] = "8]"
        if (coordCount != 2) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following part of the city coordinate doesn't adhere to format (wrong token count): " << allTokens[0] << std::endl;
            extractFailReason = oss.str();

            delete[] coordTokens;
            delete[] allTokens;
            coordTokens = nullptr;
            allTokens = nullptr;
            return false;
        }

        // The coord tokens should start and end with '[' and ']' respectively
        std::string minCoordStr = coordTokens[0], maxCoordStr = coordTokens[1];
        if (minCoordStr[0] != '[' || maxCoordStr[maxCoordStr.length() - 1] != ']') {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Following part of the city data line doesn't adhere to format (missing brackets): " << allTokens[0] << std::endl;
            extractFailReason = oss.str();

            delete[] coordTokens;
            delete[] allTokens;
            coordTokens = nullptr;
            allTokens = nullptr;
            return false;
        }

        // Actual extraction of the coordX and coordY from the string
        try {
            minCoordStr.erase(0, 1);
            maxCoordStr.pop_back();
            xCoord = std::stoi(minCoordStr);
            yCoord = std::stoi(maxCoordStr);
        } catch (const std::exception &e) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << e.what() << std::endl;
            extractFailReason = oss.str();

            delete[] coordTokens;
            delete[] allTokens;
            coordTokens = nullptr;
            allTokens = nullptr;
            return false;
        }

        // CoordX and CoordY extracted - check if they are out of bounds
        // NOTE: This part of the code assumes that the gridData.bottomLeft and gridData.topRight is already initialized
        if (xCoord < gridData.bottomLeft.x || xCoord > gridData.topRight.x ||
            yCoord < gridData.bottomLeft.y || yCoord > gridData.topRight.y) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Coordinates from the following line are out of range: " << cityLine << std::endl;
            oss << "Actual range X: " << gridData.bottomLeft.x << ", " << gridData.topRight.x << std::endl;
            oss << "Actual range Y: " << gridData.bottomLeft.y << ", " << gridData.topRight.y << std::endl;
            extractFailReason = oss.str();

            delete[] coordTokens;
            delete[] allTokens;
            coordTokens = nullptr;
            allTokens = nullptr;
            return false;
        }
        delete[] coordTokens;
        coordTokens = nullptr;
    }

    // Try to extract the city ID and name, and save it
    int cityID = 0;
    try {
        cityID = std::stoi(allTokens[1]);
        if (cityID < 0 || cityID >= CITY_ID_COUNT) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "City ID out of range (0-" << (CITY_ID_COUNT - 1) << "): " << std::endl;
            oss << cityLine;
            Utils::PrintNewlines(2, oss);
            extractFailReason = oss.str();

            delete[] allTokens;
            allTokens = nullptr;
            return false;
        }

        // Check for conflicts
        //
        // If the new 'city name' associated with a 'city ID' clashes
        // with what currently exists in the 'cityNames' array/map
        const std::string newCityName = allTokens[2];
        const std::string currCityName = gridData.cityNames[cityID];
        if (newCityName.empty()) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "City name is empty on following line: " << cityLine << std::endl;
            Utils::PrintNewlines(1, oss);
            extractFailReason = oss.str();

            delete[] allTokens;
            allTokens = nullptr;
            return false;
        }
        if (!currCityName.empty() && currCityName != newCityName) {
            std::ostringstream oss;
            oss << "=== Extracting city data failure ===" << std::endl;
            oss << "Attempting to override existing city name with new name: " << cityLine << std::endl;
            Utils::PrintNewlines(1, oss);
            extractFailReason = oss.str();

            delete[] allTokens;
            allTokens = nullptr;
            return false;
        }

        // Actual saving of the city ID into the array
        gridData.cityNames[cityID] = newCityName;
    } catch (const std::exception &e) {
        std::ostringstream oss;
        oss << "=== Extracting city data failure ===" << std::endl;
        oss << e.what() << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    // The actual saving of the data into the "gridData" reference
    if (xCoord < gridData.bottomLeft.x || xCoord > gridData.topRight.x ||
        yCoord < gridData.bottomLeft.x || yCoord > gridData.topRight.y) {
        std::ostringstream oss;
        oss << "=== Extract city data failure ===" << std::endl;
        oss << "Following XY coord is out of grid range: " << xCoord << ", " << yCoord << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    const int xAdjusted = xCoord - gridData.bottomLeft.x;
    const int yAdjusted = yCoord - gridData.bottomLeft.y;
    gridData.cityGrid[xAdjusted][yAdjusted] = cityID;

    delete[] allTokens;
    allTokens = nullptr;
    return true;
}

bool DataLoader::ReadGenericTextFile(const std::string &filePath, GridData &gridData, std::string &readFailReason, const bool cloudOrPressure) {
    std::ifstream dataFile(filePath);
    if (!dataFile.is_open()) {
        readFailReason = "Failed to open file: " + filePath;
        return false;
    }

    std::string aLine;
    while (std::getline(dataFile, aLine)) {
        if (aLine.empty()) {
            continue;
        }
        std::string extractFailReason = "";
        const bool extractSuccess = DataLoader::ExtractGenericDataLine(aLine, gridData, extractFailReason, cloudOrPressure);
        if (!extractSuccess) {
            readFailReason = extractFailReason;
            return false;
        }
    }
    return true;
}

bool DataLoader::ExtractGenericDataLine(const std::string &dataLine, GridData &gridData, std::string &extractFailReason, const bool cloudOrPressure) {
    const std::string cloudOrPressureStr = cloudOrPressure ? "cloud" : "pressure";

    int tokenCount = 0;
    std::string *allTokens = Utils::TokenizeString(dataLine, "-", tokenCount);
    if (tokenCount != 2) {
        std::ostringstream oss;
        oss << "=== Extract " << cloudOrPressureStr << " data failure ===" << std::endl;
        oss << "Following line has wrong format (wrong token count): " << dataLine << std::endl;
        extractFailReason = oss.str();
        return false;
    }

    // Extract the x and y coordinates from the first token e.g [4, 7]
    int xCoord = 0, yCoord = 0;
    {
        int coordTokenCount = 0;
        std::string *coordTokens = Utils::TokenizeString(allTokens[0], ",", coordTokenCount, true);

        // [0] - "[3", [1] - "7]"
        if (coordTokenCount != 2) {
            std::ostringstream oss;
            oss << "=== Extract " << cloudOrPressure << " data failure ===" << std::endl;
            oss << "Following line has wrong format (wrong token count): " << allTokens[0] << std::endl;
            extractFailReason = oss.str();

            delete[] allTokens;
            delete[] coordTokens;
            allTokens = nullptr;
            coordTokens = nullptr;
            return false;
        }

        std::string xCoordStr = coordTokens[0];
        std::string yCoordStr = coordTokens[1];
        // std::cout << "First: " << xCoordStr[0] << std::endl;
        // std::cout << "Last: " << yCoordStr.back() << std::endl;
        if (xCoordStr[0] != '[' || yCoordStr.back() != ']') {
            std::ostringstream oss;
            oss << "=== Extract " << cloudOrPressure << " data failure ===" << std::endl;
            oss << "Following line has wrong format (missing brackets): " << allTokens[0] << std::endl;
            extractFailReason = oss.str();

            delete[] allTokens;
            delete[] coordTokens;
            allTokens = nullptr;
            coordTokens = nullptr;
            return false;
        }

        xCoordStr.erase(0, 1);
        yCoordStr.pop_back();
        try {
            xCoord = std::stoi(xCoordStr);
            yCoord = std::stoi(yCoordStr);
        } catch (const std::exception &e) {
            std::ostringstream oss;
            oss << "=== Extract " << cloudOrPressure << " data failure ===" << std::endl;
            oss << e.what() << std::endl;
            extractFailReason = oss.str();

            delete[] allTokens;
            delete[] coordTokens;
            allTokens = nullptr;
            coordTokens = nullptr;
            return false;
        }
        delete[] coordTokens;
        coordTokens = nullptr;
    }

    // Extract the cell value
    int cellValue = 0;
    {
        try {
            cellValue = std::stoi(allTokens[1]);
        } catch (const std::exception &e) {
            delete[] allTokens;
            allTokens = nullptr;
            return false;
        }
    }

    if (xCoord < gridData.bottomLeft.x || xCoord > gridData.topRight.x ||
        yCoord < gridData.bottomLeft.x || yCoord > gridData.topRight.y) {
        std::ostringstream oss;
        oss << "=== Extract " << cloudOrPressureStr << " data failure ===" << std::endl;
        oss << "Following XY coord is out of grid range: " << xCoord << ", " << yCoord << std::endl;
        extractFailReason = oss.str();

        delete[] allTokens;
        allTokens = nullptr;
        return false;
    }

    // Set the extracted coordinate value with the extracted value for that grid cell
    const int xAdjusted = xCoord - gridData.bottomLeft.x;
    const int yAdjusted = yCoord - gridData.bottomLeft.y;
    if (cloudOrPressure) {
        gridData.cloudGrid[xAdjusted][yAdjusted] = cellValue;
    } else {
        gridData.pressureGrid[xAdjusted][yAdjusted] = cellValue;
    }
    delete[] allTokens;
    allTokens = nullptr;
    return true;
}