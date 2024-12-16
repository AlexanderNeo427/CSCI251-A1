#include "weatherApp.hpp"
#include <iostream>
#include <map>

int main() {
    std::map<GRID_TYPE, GridData> allGrids;
    while (true) {
        Utils::PrintNewlines(3);
        WeatherApp::PrintMainMenu();

        const InputData inputData = WeatherApp::AwaitUserInput();
        if (!inputData.isValid) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            std::cin.ignore();
            continue;
        }

        const OPTION userOption = static_cast<OPTION>(inputData.numChoice);
        if (userOption == OPTION::QUIT) {
            break;
        }
        std::cout << "[ " << ALL_OPTIONS.at(userOption) << " ]";
        Utils::PrintNewlines(2);

        const GenericStatus handleOptionStatus = WeatherApp::HandleOption(userOption, allGrids);
        if (!handleOptionStatus.status) {
            std::cout << handleOptionStatus.message << std::endl;
            continue;
        }
    }

    // Cleanup
    for (const std::pair<const GRID_TYPE, GridData> &grid : allGrids) {
        const GridData data = grid.second;
        for (int x = 0; x < (data.rangeX.max - data.rangeX.min) + 1; x++) {
            delete[] data.arr[x];
        }
        delete[] data.arr;
    }
    return EXIT_SUCCESS;
};
