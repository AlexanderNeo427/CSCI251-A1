#include "Input.h"
#include "Declarations.h"
#include <iostream>

bool Input::AwaitStrInput(std::string &strInput, std::string &message, const std::string &prompt = "") {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::cout << ANSI::YELLOW;

    std::getline(std::cin, strInput);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cout << ANSI::DEFAULT;
        message = "std::cin failure, please try again....";
        return false;
    }
    std::cout << ANSI::DEFAULT;
    return true;
};

bool Input::AwaitCharInput(char &charInput, std::string& message, const std::string &prompt = "") {
    std::string strInput, strInputStatus;

    const bool success = Input::AwaitStrInput(strInput, strInputStatus, prompt);
    if (!success) {
        message = strInputStatus;
        return false;
    }

    if (strInput.length() != 1) {
        message = "Please enter a valid character";
        return false;
    }
    return true;
};

bool Input::AwaitIntInput(int &intInput, std::string& message, const std::string &prompt = "") {
    try {
        std::string strInput, strInputStatus;
        
        const bool success = Input::AwaitStrInput(strInput, strInputStatus);
        if (!success) {
            message = strInputStatus;
            return false;
        }
        
        intInput = std::stoi(strInput);
        return true;
    }
    catch (const std::exception& e) {
        message = e.what();
        return false;
    }
    return true;
}