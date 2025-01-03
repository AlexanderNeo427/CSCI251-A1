#include "Utils.hpp"
#include "WeatherApp.hpp"
#include <iostream>

int main() {
    std::map<GRID_TYPE, GridData> allGrids;
    std::map<CityID, std::string> cityLookupTable;

    while (true) {
        std::cout << ANSI::DEFAULT;
        Utils::PrintNewlines(2);
        WeatherApp::PrintMainMenu();

        const InputData inputData = WeatherApp::AwaitUserInput();
        if (!inputData.isValid) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            std::cin.ignore();
            continue;
        }

        const MENU_OPTION userOption = static_cast<MENU_OPTION>(inputData.numChoice);
        if (userOption == MENU_OPTION::QUIT) {
            break;
        }

        std::cout << "[ " << ALL_OPTIONS.at(userOption) << " ]";
        Utils::PrintNewlines(2);

        const GenericStatus handleOptionStatus = WeatherApp::HandleOption(userOption, allGrids, cityLookupTable);
        if (!handleOptionStatus.status) {
            std::cout << handleOptionStatus.message << std::endl;
            continue;
        }
    }

    // Cleanup
    for (const std::pair<const GRID_TYPE, GridData> &grid : allGrids) {
        GridData data = grid.second;
        const int width = (data.topRight.x - data.bottomLeft.x) + 1;
        for (int x = 0; x < width; x++) {
            delete[] data.arr[x];
            data.arr[x] = nullptr;
        }
        delete[] data.arr;
        data.arr = nullptr;
    }
    return EXIT_SUCCESS;
};
