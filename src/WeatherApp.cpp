#include "WeatherApp.hpp"
#include "DataLoader.hpp"
#include "SummaryReport.hpp"
#include "Utils.hpp"
#include <iostream>

void WeatherApp::PrintMainMenu() {
    std::cout << ANSI::BLUE << std::endl;
    std::cout << "Student ID:   9085610" << std::endl;
    std::cout << "Student Name: Alexander Neo" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Welcome to Weather Information Processing System!";
    std::cout << ANSI::DEFAULT;
    Utils::PrintNewlines(2);

    for (const std::pair<OPTION, std::string> op : ALL_OPTIONS) {
        std::cout << static_cast<int>(op.first) << ")    " << op.second << std::endl;
    }
    Utils::PrintNewlines(1);
    std::cout << "Please enter your choice: ";
};

InputData WeatherApp::AwaitUserInput() {
    std::string userInput;
    std::getline(std::cin, userInput);
    if (std::cin.fail() || userInput.length() != 1 || userInput[0] < '0' || userInput[0] > '9') {
        std::cin.clear();
        return InputData(false);
    }
    return InputData(true, std::stoi(userInput));
};

void WeatherApp::RenderGrid(const GridData &gridData, const RENDER_MODE renderMode, const unsigned int padAmount) {
    const int contentWidth = (gridData.topRight.x - gridData.bottomLeft.x) + 1;
    const int contentHeight = (gridData.topRight.y - gridData.bottomLeft.y) + 1;

    // Top border
    std::cout << "   " << ANSI::WHITE;
    for (int i = 0; i < (contentWidth + 2); i++) {
        Utils::PaddedPrint("#", padAmount);
    }
    std::cout << std::endl;

    const std::vector<std::string> colorWheel = {
        ANSI::RED,
        ANSI::GREEN,
        ANSI::BLUE,
        ANSI::YELLOW,
        ANSI::CYAN,
    };
    unsigned int currColorIndex = 0;

    // Content | Middle borders | Y coordinates
    std::map<int, std::string> numToColor;
    for (int y = contentHeight - 1; y >= 0; y--) {
        std::cout << ANSI::DEFAULT << " " << y << " ";

        std::cout << ANSI::WHITE;
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
                    std::cout << numToColor[gridVal];
                    Utils::PaddedPrint(gridVal, padAmount);
                }
            }
        } else if (renderMode == RENDER_MODE::INDEX) {
            for (int x = 0; x < contentWidth; x++) {
                const double value = static_cast<double>(gridData.arr[x][y]);
                const int indexVal = floor(value / 10.);
                if (numToColor.count(indexVal) == 0) {
                    numToColor[indexVal] = colorWheel[currColorIndex];
                    currColorIndex = (currColorIndex + 1) % colorWheel.size();
                }
                std::cout << numToColor[indexVal];
                Utils::PaddedPrint(indexVal, padAmount);
            }
        } else if (renderMode == RENDER_MODE::LMH) {
            for (int x = 0; x < contentWidth; x++) {
                const char lmh = Utils::GetLMH(gridData.arr[x][y]);
                if (lmh == 'L') {
                    std::cout << ANSI::GREEN;
                } else if (lmh == 'M') {
                    std::cout << ANSI::YELLOW;
                } else if (lmh == 'H') {
                    std::cout << ANSI::RED;
                }
                Utils::PaddedPrint(lmh, padAmount);
            }
        }
        std::cout << ANSI::WHITE;
        std::cout << "#" << std::endl;
    }

    // Bottom border
    std::cout << "   " << ANSI::WHITE;
    for (int i = 0; i < (contentWidth + 2); i++) {
        Utils::PaddedPrint("#", padAmount);
    }
    std::cout << std::endl;

    // X coordinates
    std::cout << ANSI::DEFAULT;
    std::cout << "   ";
    Utils::PaddedPrint(" ", padAmount);
    for (int i = 0; i < contentWidth; i++) {
        Utils::PaddedPrint(i, padAmount);
    }
    std::cout << std::endl;
};

/**
 * @param refAllGrids Mutable reference to the grid data
 */
GenericStatus WeatherApp::HandleOption(
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