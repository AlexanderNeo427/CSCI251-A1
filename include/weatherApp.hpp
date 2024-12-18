#ifndef WEATHER_APP_H
#define WEATHER_APP_H

#include "dataLoader.hpp"
#include "declarations.hpp"
#include "summaryReport.hpp"
#include <cmath>
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

    void AwaitEnterInput() {}

    void RenderGrid(const GridData &gridData, const RENDER_MODE renderMode, const int padAmount = 2) {
        const int contentWidth = (gridData.topRight.x - gridData.bottomLeft.x) + 1;
        const int contentHeight = (gridData.topRight.y - gridData.bottomLeft.y) + 1;

        const std::vector<CONSOLE_COLOR> colorWheel = {
            CONSOLE_COLOR::RED,
            CONSOLE_COLOR::GREEN,
            CONSOLE_COLOR::BLUE,
            CONSOLE_COLOR::YELLOW,
            CONSOLE_COLOR::CYAN,
            CONSOLE_COLOR::MAGENTA,
        };
        int currColorIndex = 0;

        // Top border
        Utils::SetConsoleColor(CONSOLE_COLOR::WHITE);
        Utils::PaddedPrint(" ", padAmount);
        for (int i = 0; i < (contentWidth + 2); i++) {
            Utils::PaddedPrint("#", padAmount);
        }
        std::cout << std::endl;

        // Content | Middle borders | Y coordinates
        std::map<int, CONSOLE_COLOR> numToColor;
        for (int y = contentHeight - 1; y >= 0; y--) {
            Utils::ResetConsoleColor();
            std::cout << " " << y << " ";
            for (int i = 0; i < std::min(0, padAmount - 2); i++) {
                std::cout << " ";
            }

            Utils::SetConsoleColor(CONSOLE_COLOR::WHITE);
            Utils::PaddedPrint("#", padAmount);
            if (renderMode == RENDER_MODE::CITY) {
                for (int x = 0; x < contentWidth; x++) {
                    const int gridVal = gridData.arr[x][y];
                    if (gridVal == 0) {
                        Utils::PaddedPrint(" ", padAmount);
                    } else {
                        if (numToColor.count(gridVal) == 0) {
                            numToColor[gridVal] = colorWheel[currColorIndex];
                            currColorIndex = (currColorIndex + 1) % colorWheel.size();
                        }
                        Utils::SetConsoleColor(numToColor[gridVal]);
                        Utils::PaddedPrint(gridVal, padAmount);
                    }
                }
            } else if (renderMode == RENDER_MODE::INDEX) {
                for (int x = 0; x < contentWidth; x++) {
                    const double value = static_cast<double>(gridData.arr[x][y]);
                    const int indexVal = floor(value / 10.);
                    // if (numToColor.count(indexVal) == 0) {
                    //     numToColor[indexVal] = colorWheel[currColorIndex];
                    //     currColorIndex = (currColorIndex + 1) % colorWheel.size();
                    // }
                    // Utils::SetConsoleColor(numToColor[indexVal]);
                    std::cout << "\033[38;5;" << 160 << "m";
                    Utils::PaddedPrint(indexVal, padAmount);
                }
            } else if (renderMode == RENDER_MODE::LMH) {
                for (int x = 0; x < contentWidth; x++) {
                    const char lmh = Utils::GetLMH(gridData.arr[x][y]);
                    if (lmh == 'L') {
                        // Utils::SetConsoleColor(CONSOLE_COLOR::GREEN);
                        std::cout << "\033[38;5;" << 46 << "m";
                    } else if (lmh == 'M') {
                        std::cout << "\033[38;5;" << 226 << "m";
                        // Utils::SetConsoleColor(CONSOLE_COLOR::YELLOW);
                    } else if (lmh == 'H') {
                        std::cout << "\033[38;5;" << 160 << "m";
                        // Utils::SetConsoleColor(CONSOLE_COLOR::RED);
                    }
                    Utils::PaddedPrint(lmh, padAmount);
                }
            }
            Utils::SetConsoleColor(CONSOLE_COLOR::WHITE);
            std::cout << "#" << std::endl;
        }

        // Bottom border
        Utils::SetConsoleColor(CONSOLE_COLOR::WHITE);
        Utils::PaddedPrint(" ", padAmount);
        for (int i = 0; i < (contentWidth + 2); i++) {
            Utils::PaddedPrint("#", padAmount);
        }
        std::cout << std::endl;

        // X coordinates
        Utils::ResetConsoleColor();
        for (int i = 0; i < 2; i++) {
            Utils::PaddedPrint(" ", padAmount);
        }
        for (int i = 0; i < contentWidth; i++) {
            Utils::PaddedPrint(i, padAmount);
        }
        std::cout << std::endl;
    };

    /**
     * @param refAllGrids Mutable reference to the grid data
     */
    GenericStatus HandleOption(
        const OPTION option,
        std::map<GRID_TYPE, GridData> &refAllGrids,
        std::map<CityID, std::string> &refCityLookupTable) {

        switch (option) {
            case OPTION::PROCESS_CONFIG_FILE: {
                const ConfigDataStatus configDataStatus = DataLoader::GetConfigData("./data/config.txt");
                if (!configDataStatus.status) {
                    return GenericStatus(false, "Error loading data from config file");
                }
                const ConfigData &cfg = configDataStatus.configData;
                refAllGrids[GRID_TYPE::CITY] = DataLoader::LoadCityLocations(cfg.cityLocations, cfg, refCityLookupTable);
                refAllGrids[GRID_TYPE::COVERAGE] = DataLoader::LoadGenericData(cfg.cloudCoverages, cfg);
                refAllGrids[GRID_TYPE::PRESSURE] = DataLoader::LoadGenericData(cfg.atmosPressures, cfg);
                break;
            }
            case OPTION::DISPLAY_CITY_MAP:
                RenderGrid(refAllGrids[GRID_TYPE::CITY], RENDER_MODE::CITY);
                break;
            case OPTION::COVERAGE_MAP_IDX:
                RenderGrid(refAllGrids[GRID_TYPE::COVERAGE], RENDER_MODE::INDEX);
                break;
            case OPTION::COVERAGE_MAP_LMH:
                RenderGrid(refAllGrids[GRID_TYPE::COVERAGE], RENDER_MODE::LMH);
                break;
            case OPTION::ATMOS_PRESSURE_IDX:
                RenderGrid(refAllGrids[GRID_TYPE::PRESSURE], RENDER_MODE::INDEX);
                break;
            case OPTION::ATMOS_PRESSURE_LMH:
                RenderGrid(refAllGrids[GRID_TYPE::PRESSURE], RENDER_MODE::LMH);
                break;
            case OPTION::SUMMARY_REPORT: {
                SummaryReport::GenerateSummaryReport(refAllGrids, refCityLookupTable);
                break;
            }
            default: break;
        }
        return GenericStatus(true);
    };
}; // namespace WeatherApp

#endif