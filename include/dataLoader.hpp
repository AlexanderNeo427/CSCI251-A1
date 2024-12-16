#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "declarations.hpp"
#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace DataLoader {
    /**
     * @return The data from the config file, bundled into a 'ConfigDataStatus' struct
     */
    ConfigDataStatus GetConfigData(const std::string &filePath) {
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
                    configData.rangeX.min = rangeMin;
                    configData.rangeX.max = rangeMax;
                } else {
                    configData.rangeY.min = rangeMin;
                    configData.rangeY.max = rangeMax;
                }
            } else if (Utils::StrContains(line, "citylocation.txt")) { // Set the 'city location' data
                const ReadFileStatus rawLocationData = Utils::ReadLinesFromFile(line);
                if (!rawLocationData.status) {
                    return ConfigDataStatus(false);
                }
                configData.cityLocationEntries = rawLocationData.allLines;
            } else if (Utils::StrContains(line, "cloudcover.txt")) { // Set the 'cloud coveragea' data
                const ReadFileStatus rawCoverageData = Utils::ReadLinesFromFile(line);
                if (!rawCoverageData.status) {
                    return ConfigDataStatus(false);
                }
                configData.coverageEntries = rawCoverageData.allLines;
            } else if (Utils::StrContains(line, "pressure.txt")) { // Set the 'pressure' data
                const ReadFileStatus rawPressureData = Utils::ReadLinesFromFile(line);
                if (!rawPressureData.status) {
                    return ConfigDataStatus(false);
                }
                configData.pressureEntries = rawPressureData.allLines;
            }
        }
        return ConfigDataStatus(true, configData);
    }

    GridData LoadCityLocations(const std::vector<std::string> &cityLocationData, const ConfigData &cfg) {
        const int width = (cfg.rangeX.max - cfg.rangeX.min) + 1;
        const int height = (cfg.rangeY.max - cfg.rangeY.min) + 1;

        auto grid = GridData();
        grid.rangeX.min = cfg.rangeX.min;
        grid.rangeX.max = cfg.rangeX.max;
        grid.rangeY.min = cfg.rangeY.min;
        grid.rangeY.max = cfg.rangeY.max;

        grid.arr = new int *[width];
        for (int x = 0; x < width; x++) {
            grid.arr[x] = new int[height];
            for (int y = 0; y < height; y++) {
                grid.arr[x][y] = 0;
            }
        }

        for (const std::string &datum : cityLocationData) { // (e.g datum = [3, 5]-3-Big_City)
            const std::vector<std::string> splitData = Utils::StrSplit(datum, '-');
            const int cityType = std::stoi(splitData[1]);

            std::string locStr = splitData[0];              // Extract location info (e.g [23, 9])
            locStr = locStr.substr(1, locStr.length() - 2); // Remove the '[' and ']' chars
            const std::vector<std::string> locData = Utils::StrSplit(locStr, ',');
            const int posX = std::stoi(locData[0]);
            const int posY = std::stoi(locData[1]);
            std::cout << "City Type: " <<  cityType << std::endl;
            std::cout << "Pos: " << posX << ", " << posY << std::endl << std::endl;
            grid.arr[posX][posY] = cityType;
        }

        std::cout << "Print grid to validate....";
        Utils::PrintNewlines(3);
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                std::cout << grid.arr[x][y];
            }
            std::cout << std::endl;
        }
        return grid;
    }

    // Grid LoadCloudCover(const std::vector<std::string> &cloudCoverageData) {
    //     return nullptr;
    // }
    //
    // int **LoadPressureData(const std::vector<std::string> &pressureData) {
    //     return nullptr;
    // }
} // namespace DataLoader

#endif