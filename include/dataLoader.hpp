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
     * @return The data from the config file, bundled into a struct
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
                    configData.minX = rangeMin;
                    configData.maxX = rangeMax;
                }
                else {
                    configData.minY = rangeMin;
                    configData.maxY = rangeMax;
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
                configData.cloudCover = rawCoverageData.allLines;
            } else if (Utils::StrContains(line, "pressure.txt")) { // Set the 'pressure' data
                const ReadFileStatus rawPressureData = Utils::ReadLinesFromFile(line);
                if (!rawPressureData.status) { 
                    return ConfigDataStatus(false); 
                }
                configData.pressure = rawPressureData.allLines;
            }
        }
        return ConfigDataStatus(true, configData);
    }

    int **LoadCityLocations(const std::vector<std::string> &cityLocationData) {
        return nullptr;
    }

    int **LoadCloudCover(const std::vector<std::string> &cloudCoverageData) {
        return nullptr;
    }

    int **LoadPressureData(const std::vector<std::string> &pressureData) {
        return nullptr;
    }
} // namespace DataLoader

#endif