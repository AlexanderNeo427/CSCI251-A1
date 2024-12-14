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
     * @brief 'out' params are to be filled-in by the functions
     * @return bool Success/status of loading the config file data
     */
    bool LoadConfigFile(const std::string &filePath) {

        const ReadFileStatus configFileData = Utils::ReadLinesFromFile(filePath);
        if (!configFileData.status) {
            std::cout << "Error reading from file at: " << filePath << std::endl;
            return false;
        }

        for (std::string line : configFileData.allLines) {
            if (line.empty() || line.find("//") == 0) {
                continue;
            }
            if (Utils::StrContains(line, "=")) {
                const std::vector<std::string> data = Utils::StrSplit(line, '=');
                const std::string axisKey = data[0];

                const std::vector<std::string> gridRange = Utils::StrSplit(data[1], '-');
                const int rangeMin = std::stoi(gridRange[0]);
                const int rangeMax = std::stoi(gridRange[1]);

                if (axisKey == "GridIdxRange") {

                } else {
                }
            } else if (Utils::StrContains(line, "citylocation.txt")) {
                const ReadFileStatus rawLocationData = Utils::ReadLinesFromFile(line);
                if (!rawLocationData.status) {
                    return false;
                }

            } else if (Utils::StrContains(line, "cloudcover.txt")) {
                const ReadFileStatus rawCoverageData = Utils::ReadLinesFromFile(line);
                if (!rawCoverageData.status) {
                    return false;
                }
            } else if (Utils::StrContains(line, "pressure.txt")) {
                const ReadFileStatus rawPressureData = Utils::ReadLinesFromFile(line);
                if (!rawPressureData.status) {
                    return false;
                }
            }
        }
        return true;
    }

    int **LoadCityLocations(const std::vector<std::string> &rawLocationData) {
        return nullptr;
    }

    int **LoadCloudCover(const std::vector<std::string> &rawCoverageData) {
        return nullptr;
    }

    int **LoadPressureData(const std::vector<std::string> &rawPressureData) {
        return nullptr;
    }
} // namespace DataLoader

#endif