#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace FileOperations {
    void ProcessConfigFile(const std::string &filePath) {
        std::vector<std::string> filesToProcess;

        std::ifstream configFile(filePath);
        if (!configFile) {
            std::cout << "Error reading from file at: " << filePath << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            if (line.empty() || line.find("//") == 0) {
                continue;
            }
            if (Utils::StrContains(line, '=')) {
                const std::vector<std::string> data = Utils::StrSplit(line, '=');
                const std::string axisKey = data[0];

                const std::vector<std::string> gridRange = Utils::StrSplit(data[1], '-');
                const int rangeMin = std::stoi(gridRange[0]);
                const int rangeMax = std::stoi(gridRange[1]);

                std::cout << "Axis key: " << axisKey << std::endl;
                std::cout << "Range min: " << rangeMin << std::endl;
                std::cout << "Range max: " << rangeMax << std::endl;

                continue;
            }
        }
        configFile.close();
    }
} // namespace FileOperations

#endif