#include "weatherApp.hpp"
#include <iostream>

int main() {
    // int **pCityMap = nullptr;
    // int **pCloudGrid = nullptr;
    // int **pPressureGrid = nullptr;

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

    // TODO: De-allocate memory

    return EXIT_SUCCESS;
};
