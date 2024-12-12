#include "weatherApp.hpp"
#include <iostream>

int main() {
    int **g_pCityMap = nullptr;
    int **g_pCloudMap = nullptr;
    int **g_pPressureGrid = nullptr;

    while (true) {
        for (int i = 0; i < 3; i++) {
            std::cout << std::endl;
        }

        WeatherApp::PrintMainMenu();

        const InputStatus inputStatus = WeatherApp::AwaitUserInput();
        if (!inputStatus.status || std::cin.fail()) {
            std::cin.clear();
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            continue;
        }

        const ChoiceStatus choiceStatus = WeatherApp::GetChoiceStatus(inputStatus.userInput);
        if (!choiceStatus.status) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            continue;
        }

        const OPTION userOption = static_cast<OPTION>(choiceStatus.choice);
        if (userOption == OPTION::QUIT) {
            break;
        }
        
        std::cout << "[ " << allOptions.at(userOption) << " ]" << std::endl
                  << std::endl;

        if (userOption == OPTION::PROCESS_CONFIG_FILE) {
            
        }
    }

    delete g_pCityMap;
    delete g_pCloudMap;
    delete g_pPressureGrid;

    return EXIT_SUCCESS;
};
