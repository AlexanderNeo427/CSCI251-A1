#include "DataLoader.hpp"
#include "Utils.hpp"
#include <iostream>

/**
 * @return The data from the config file, bundled into a 'ConfigDataStatus' struct
 */
ConfigDataStatus DataLoader::GetConfigData(const std::string &filePath) {
    const ReadFileStatus configFileData = Utils::ReadLinesFromFile(filePath);
    if (!configFileData.status) {
        std::cout << "Error reading from file at: " << filePath << std::endl;
        return ConfigDataStatus(false);
    }

    auto configData = ConfigData();
    for (const std::string &line : configFileData.allLines) {
        if (line.empty() || line.find("//") == 0) { // Ignore empty lines & comments
            continue;
        }
        if (Utils::StrContains(line, "=")) { // Set the 'grid idx range'
            const std::vector<std::string> data = Utils::StrSplit(line, '=');
            const std::string axisKey = data[0];

            const std::vector<std::string> gridRange = Utils::StrSplit(data[1], '-');
            const int rangeMin = std::stoi(gridRange[0]);
            const int rangeMax = std::stoi(gridRange[1]);

            if (axisKey == "GridX_IdxRange") {
                configData.bottomLeft.x = rangeMin;
                configData.topRight.x = rangeMax;
            } else {
                configData.bottomLeft.y = rangeMin;
                configData.topRight.y = rangeMax;
            }
        } else if (Utils::StrContains(line, "citylocation.txt")) { // Set the 'city location' data
            const ReadFileStatus rawLocationData = Utils::ReadLinesFromFile(line);
            if (!rawLocationData.status) {
                return ConfigDataStatus(false);
            }
            configData.cityLocations = rawLocationData.allLines;
        } else if (Utils::StrContains(line, "cloudcover.txt")) { // Set the 'cloud coveragea' data
            const ReadFileStatus rawCoverageData = Utils::ReadLinesFromFile(line);
            if (!rawCoverageData.status) {
                return ConfigDataStatus(false);
            }
            configData.cloudCoverages = rawCoverageData.allLines;
        } else if (Utils::StrContains(line, "pressure.txt")) { // Set the 'pressure' data
            const ReadFileStatus rawPressureData = Utils::ReadLinesFromFile(line);
            if (!rawPressureData.status) {
                return ConfigDataStatus(false);
            }
            configData.atmosPressures = rawPressureData.allLines;
        }
    }
    return ConfigDataStatus(true, configData);
}

GridData DataLoader::LoadCityLocations(
    const std::vector<std::string> &cityLocationData,
    const ConfigData &cfg,
    std::map<int, std::string> &refCityLookupTable) {

    const int width = (cfg.topRight.x - cfg.bottomLeft.x) + 1;
    const int height = (cfg.topRight.y - cfg.bottomLeft.y) + 1;

    auto grid = GridData();
    grid.bottomLeft = cfg.bottomLeft;
    grid.topRight = cfg.topRight;

    grid.arr = new int *[width];
    for (int x = 0; x < width; x++) {
        grid.arr[x] = new int[height];
        for (int y = 0; y < height; y++) {
            grid.arr[x][y] = 0;
        }
    }

    for (const std::string &datum : cityLocationData) { // (e.g datum = [3, 5]-3-Big_City)
        const std::vector<std::string> &splitData = Utils::StrSplit(datum, '-');
        const int cityType = std::stoi(splitData[1]);

        std::string locStr = splitData[0];              // Extract location info (e.g [23, 9])
        locStr = locStr.substr(1, locStr.length() - 2); // Remove the '[' and ']' chars
        const std::vector<std::string> locData = Utils::StrSplit(locStr, ',');
        const int posX = std::stoi(locData[0]);
        const int posY = std::stoi(locData[1]);
        grid.arr[posX][posY] = cityType;

        const std::string cityName = splitData[2];
        refCityLookupTable[cityType] = cityName;
    }
    return grid;
}

GridData DataLoader::LoadGenericData(const std::vector<std::string> &genericData, const ConfigData &cfg) {
    const int width = (cfg.topRight.x - cfg.bottomLeft.x) + 1;
    const int height = (cfg.topRight.y - cfg.bottomLeft.y) + 1;

    auto grid = GridData();
    grid.bottomLeft = cfg.bottomLeft;
    grid.topRight = cfg.topRight;

    grid.arr = new int *[width];
    for (int x = 0; x < width; x++) {
        grid.arr[x] = new int[height];
        for (int y = 0; y < height; y++) {
            grid.arr[x][y] = 0;
        }
    }

    for (const std::string &datum : genericData) { // Example Datum: [7, 4]-34
        const std::vector<std::string> &splitData = Utils::StrSplit(datum, '-');

        std::string locStr = splitData[0];              // Extract location info (e.g [23, 9])
        locStr = locStr.substr(1, locStr.length() - 2); // Remove the '[' and ']' chars
        const std::vector<std::string> locData = Utils::StrSplit(locStr, ',');
        const int posX = std::stoi(locData[0]);
        const int posY = std::stoi(locData[1]);
        const int indexValue = std::stoi(splitData[1]);

        grid.arr[posX][posY] = indexValue;
    }
    return grid;
}