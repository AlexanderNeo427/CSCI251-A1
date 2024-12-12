#ifndef WEATHER_APP
#define WEATHER_APP

#include "declarations.hpp"
#include <cstdint>
#include <iostream>

namespace WeatherApp {
    void print_main_menu() {
        std::cout << "Student ID: 9085610" << std::endl;
        std::cout << "Student Name: Alexander Neo" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Welcome to Weather Information Processing System!" << std::endl
                  << std::endl;
        for (const std::pair<OPTION, std::string> op : all_options) {
            const int optionNum = static_cast<int>(op.first);
            std::cout << optionNum << ")    " << op.second << std::endl;
        }
        std::cout << std::endl
                  << "Please enter your choice: ";
    };

    InputStatus await_user_input() {
        std::string user_input;
        std::getline(std::cin, user_input);
        if (user_input.empty()) {
            return InputStatus(false);
        }
        return InputStatus(true, user_input);
    };

    ChoiceStatus get_choice_status(const std::string &user_input) {
        if (user_input.length() != 1 || user_input[0] < '0' || user_input[0] > '9') {
            return ChoiceStatus(false);
        }
        return ChoiceStatus(true, std::stoi(user_input));
    }

    void handle_option(const OPTION option) {
        switch (option) {

        default:
            break;
        }
        std::cout << "Handling option: " << static_cast<int>(option) << std::endl;
    }
}; // namespace WeatherApp

#endif