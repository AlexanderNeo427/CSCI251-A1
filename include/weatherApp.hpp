#ifndef WEATHER_APP_H
#define WEATHER_APP_H

#include "dataLoader.hpp"
#include "declarations.hpp"
#include <iostream>

namespace WeatherApp {
    void PrintMainMenu() {
        std::cout << "Student ID: 9085610" << std::endl;
        std::cout << "Student Name: Alexander Neo" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Welcome to Weather Information Processing System!" << std::endl << std::endl;
        for (const std::pair<OPTION, std::string> op : ALL_OPTIONS) {
            std::cout << static_cast<int>(op.first) << ")    " << op.second << std::endl;
        }
        std::cout << std::endl << "Please enter your choice: ";
    };

    InputData AwaitUserInput() {
        std::string userInput;
        std::getline(std::cin, userInput);
        if (std::cin.fail() || userInput.length() != 1 || userInput[0] < '0' || userInput[0] > '9') {
            std::cin.clear();
            return InputData(false);
        }
        return InputData(true, std::stoi(userInput));
    };

    /**
     * @param refAllGrids Mutable reference to the grid data
     */
    GenericStatus HandleOption(const OPTION option, std::map<GRID_TYPE, GridData> &refAllGrids) {
        if (option == OPTION::PROCESS_CONFIG_FILE) {
            ConfigDataStatus configDataStatus = DataLoader::GetConfigData("./data/config.txt");
            if (!configDataStatus.status) {
                return GenericStatus(false, "Error loading data from config file");
            }
            const ConfigData& cfg = configDataStatus.configData;

            refAllGrids[GRID_TYPE::CITY] = DataLoader::LoadCityLocations(cfg.cityLocationEntries, cfg);
            
            // const GridData &cityGrid = refAllGrids[GRID_TYPE::CITY];
            // const int width = (cityGrid.rangeX.max - cityGrid.rangeX.min) + 1;
            // const int height = (cityGrid.rangeY.max - cityGrid.rangeY.min) + 1;
            // std::cout << "WH: " << width << ", " << height << std::endl;
            // for (int x = 0; x < width; x++) {
            //     for (int y = 0; y < height; y++) {
            //         std::cout << cityGrid.arr[x][y] << " SEP ";
            //     }
            //     std::cout << std::endl;
            // }
        }
        return GenericStatus(false);
    }

}; // namespace WeatherApp

#endif