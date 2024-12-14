#include "weatherApp.hpp"
#include <iostream>

int main() {
    while (true) {
        Utils::PrintNewlines(3);

        WeatherApp::PrintMainMenu();

        const InputStatus inputStatus = WeatherApp::AwaitValidInput();
        if (!inputStatus.status) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            std::cin.ignore();
            continue;
        }

        const OPTION userOption = static_cast<OPTION>(inputStatus.userInput);
        if (userOption == OPTION::QUIT) {
            break;
        }

        std::cout << "[ " << ALL_OPTIONS.at(userOption) << " ]";
        Utils::PrintNewlines(2);

        if (userOption == OPTION::PROCESS_CONFIG_FILE) {
            DataLoader::LoadConfigFile("./data/config.txt");
        }
    }

    // TODO: De-allocate memory

    return EXIT_SUCCESS;
};
