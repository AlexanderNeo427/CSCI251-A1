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
        std::cout << "Welcome to Weather Information Processing System!" << std::endl
                  << std::endl;
        for (const std::pair<OPTION, std::string> op : ALL_OPTIONS) {
            std::cout << static_cast<int>(op.first) << ")    " << op.second << std::endl;
        }
        std::cout << std::endl
                  << "Please enter your choice: ";
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
            const ConfigData &cfg = configDataStatus.configData;
            refAllGrids[GRID_TYPE::CITY] = DataLoader::LoadCityLocations(cfg.cityLocationEntries, cfg);
            refAllGrids[GRID_TYPE::COVERAGE] = DataLoader::LoadGenericData(cfg.coverageEntries, cfg);
            refAllGrids[GRID_TYPE::PRESSURE] = DataLoader::LoadGenericData(cfg.pressureEntries, cfg);
        } else if (option == OPTION::DISPLAY_CITY_MAP) {
            Renderer::RenderGrid(refAllGrids[GRID_TYPE::CITY], RENDER_MODE::CITY);
        } else if (option == OPTION::COVERAGE_MAP_IDX) {
            Renderer::RenderGrid(refAllGrids[GRID_TYPE::COVERAGE], RENDER_MODE::INDEX);
        } else if (option == OPTION::COVERAGE_MAP_LMH) {
            Renderer::RenderGrid(refAllGrids[GRID_TYPE::COVERAGE], RENDER_MODE::LMH);
        } else if (option == OPTION::ATMOS_PRESSURE_IDX) {
            Renderer::RenderGrid(refAllGrids[GRID_TYPE::PRESSURE], RENDER_MODE::INDEX);
        } else if (option == OPTION::ATMOS_PRESSURE_LMH) {
            Renderer::RenderGrid(refAllGrids[GRID_TYPE::PRESSURE], RENDER_MODE::LMH);
        } else if (option == OPTION::SUMMARY_REPORT) {
            std::cout << "TODO: Print the summary report" << std::endl;
        }
        return GenericStatus(false);
    }

}; // namespace WeatherApp

#endif