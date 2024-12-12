#include "weatherApp.hpp"
#include <iostream>

int main() {
    while (true) {
        for (int i = 0; i < 3; i++) {
            std::cout << std::endl;
        }

        WeatherApp::print_main_menu();

        const InputStatus inputStatus = WeatherApp::await_user_input();
        if (!inputStatus.status || std::cin.fail()) {
            std::cin.clear();
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            continue;
        }

        const ChoiceStatus choiceStatus = WeatherApp::get_choice_status(inputStatus.user_input);
        if (!choiceStatus.status) {
            std::cout << "Please enter a single digit number from 1-9" << std::endl;
            continue;
        }

        const OPTION user_option = static_cast<OPTION>(choiceStatus.choice);
        if (user_option == OPTION::QUIT) {
            break;
        }

        std::cout << "[ " << all_options.at(user_option) << " ]" << std::endl
                  << std::endl;
        WeatherApp::handle_option(user_option);
    }
    return EXIT_SUCCESS;
};
