#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <fstream>
#include <iostream>
#include <string>

namespace FileOperations {
    void ReadConfigFile(const std::string &filePath) {
        std::ifstream inFile(filePath);
        if (!inFile) {
            std::cout << "Error reading from file at: " << filePath << std::endl;
            return;
        }
        std::string data;
        while (std::getline(inFile, data)) {
            if (data.empty() || data.find("//") == 0) {
                continue;
            }
        }
        inFile.close();
    }
} // namespace FileOperations

#endif