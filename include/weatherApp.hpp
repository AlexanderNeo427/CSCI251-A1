#ifndef WEATHER_APP_H
#define WEATHER_APP_H

#include "dataLoader.hpp"
#include "declarations.hpp"
#include <iostream>

namespace WeatherApp {
    void PrintMainMenu() {
        std::cout << "Student ID: 9085610" << std::endl;
        std::cout << "Student Name: Alexander Neo" << std::endl;
        std::cout << "-------------------------" << std::endl;
        std::cout << "Welcome to Weather Information Processing System!" << std::endl
                  << std::endl;
        for (const std::pair<OPTION, std::string> op : ALL_OPTIONS) {
            std::cout << static_cast<int>(op.first) << ")    " << op.second << std::endl;
        }
        std::cout << std::endl
                  << "Please enter your choice: ";
    };

    InputStatus AwaitValidInput() {
        std::string userInput;
        std::getline(std::cin, userInput);
        if (std::cin.fail() || userInput.empty() || userInput.length() != 1 ||
            userInput[0] < '0' || userInput[0] > '9') {
            std::cin.clear();
            return InputStatus(false);
        }
        return InputStatus(true, std::stoi(userInput));
    };
}; // namespace WeatherApp

#endif