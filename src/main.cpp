#include "Input.h"
#include "Utils.h"
#include "WeatherApp.h"

#include <iostream>

int main() {
    GridData gridData;

    while (true) {
        std::cout << ANSI::DEFAULT;
        WeatherApp::PrintMainMenu();

        // Await valid input
        const IntInputStatus intInputStatus = Input::AwaitIntInput("Please enter your choice: ");
        if (!intInputStatus.success) {
            std::cerr << intInputStatus.message << std::endl;
        }

        // Validate input
        const int userChoice = intInputStatus.input;
        const int numOptions = static_cast<int>(MENU_OPTION::ENTRY_COUNT);
        if (userChoice < 1 || userChoice > numOptions) {
            std::cerr << "Please pick a number from 1-" << numOptions << std::endl;
            continue;
        }

        // Handle quit input
        const int choiceIndex = userChoice - 1;
        const MENU_OPTION chosenOption = static_cast<MENU_OPTION>(choiceIndex);
        if (chosenOption == MENU_OPTION::QUIT) {
            break;
        }

        // Handle the rest of the options
        std::cout << "[ " << WeatherApp::OptionToText(chosenOption) << " ]";
        Utils::PrintNewlines(2);
        WeatherApp::HandleOption(chosenOption, gridData);
    }

    // TODO: Cleanup
    const int rangeX = (gridData.topRight.x - gridData.bottomLeft.x) + 1;
    for (int x = 0; x < rangeX; x++) {
        delete[] gridData.cityGrid[x];
        delete[] gridData.cloudGrid[x];
        delete[] gridData.pressureGrid[x];
        gridData.cityGrid[x] = nullptr;
        gridData.cloudGrid[x] = nullptr;
        gridData.pressureGrid[x] = nullptr;
    }
    delete[] gridData.cityGrid;
    delete[] gridData.cloudGrid;
    delete[] gridData.pressureGrid;
    gridData.cityGrid = nullptr;
    gridData.cloudGrid = nullptr;
    gridData.pressureGrid = nullptr;
    std::cout << "Successfully reclaimed memory" << std::endl;
    return EXIT_SUCCESS;
};
