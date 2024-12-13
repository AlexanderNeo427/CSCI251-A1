#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "utils.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace FileOperations {
    void ReadConfigFile(const std::string &filePath) {
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
            if (Utils::strContains(line, '=')) {
                const std::vector<std::string> data = Utils::strSplit(line, '.');
                const std::string key = data[0];
                const std::string gridRange = data[1];
            }
            if (!Utils::strEndsWith(line, ".txt")) {
                continue;
            }

            std::ifstream inFile(line);
            if (!inFile) {
                std::cout << "Error reading from file at: " << line << std::endl;
                continue;
            }
            inFile.close();
        }
        configFile.close();
    }
} // namespace FileOperations

#endif