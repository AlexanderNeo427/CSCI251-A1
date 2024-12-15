#include "weatherApp.hpp"
#include <iostream>
#include <map>

std::map<GRID_TYPE, Grid> g_allGrids;

int main() {
    bool isRunning = true;
    while (isRunning) {
        Utils::PrintNewlines(3);
        WeatherApp::PrintMainMenu();

        const InputData inputData = WeatherApp::AwaitUserInput();
        if (!inputData.isValid) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            std::cin.ignore();
            continue;
        }

        const OPTION userOption = static_cast<OPTION>(inputData.numChoice);
        if (userOption == OPTION::QUIT) { break; }
        std::cout << "[ " << ALL_OPTIONS.at(userOption) << " ]";
        Utils::PrintNewlines(2);

        WeatherApp::HandleOption(userOption, g_allGrids);
    }

    // TODO: De-allocate memory

    return EXIT_SUCCESS;
};
