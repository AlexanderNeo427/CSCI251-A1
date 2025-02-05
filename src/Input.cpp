#include "Input.h"
#include "Declarations.h"
#include <iostream>

StrInputStatus Input::AwaitStrInput(const std::string &prompt) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::cout << ANSI::YELLOW;

    StrInputStatus retStatus;
    std::getline(std::cin, retStatus.input);
    if (std::cin.fail()) {
        std::cin.clear();
        std::cout << ANSI::DEFAULT;

        retStatus.success = false;
        retStatus.message = "std::cin input failure, please try again...";
        return retStatus;
    }
    std::cout << ANSI::DEFAULT;
    retStatus.success = true;
    return retStatus;
};

CharInputStatus Input::AwaitCharInput(const std::string &prompt) {
    CharInputStatus retStatus;

    const StrInputStatus strInputStatus = Input::AwaitStrInput(prompt);
    if (!strInputStatus.success) {
        retStatus.success = false;
        retStatus.message = strInputStatus.message;
        return retStatus;
    }

    if (strInputStatus.input.length() != 1) {
        retStatus.success = false;
        retStatus.message = "Input must be of length 1";
        return retStatus;
    }
    retStatus.input = strInputStatus.input[0];
    retStatus.success = true;
    return retStatus;
};

IntInputStatus Input::AwaitIntInput(const std::string &prompt) {
    IntInputStatus retStatus;
    try {
        const StrInputStatus strInputStatus = Input::AwaitStrInput(prompt);
        if (!strInputStatus.success) {
            retStatus.success = false;
            retStatus.message = strInputStatus.message;
            return retStatus;
        }
        const int extractedInt = std::stoi(strInputStatus.input);
        if (strInputStatus.input.find(".") != std::string::npos) {
            retStatus.success = false;
            retStatus.message = "Input::AwaitIntInput() - No floating points allowed";
            return retStatus;
        }
        retStatus.input = extractedInt;
        retStatus.success = true;
        return retStatus;
    } catch (const std::exception &e) {
        retStatus.success = false;
        retStatus.message = e.what();
        return retStatus;
    }
    retStatus.success = false;
    retStatus.message = "This is not good. This is really not good.";
    return retStatus;
}

void Input::AwaitEnterInput(const std::string &prompt) {
    if (!prompt.empty()) {
        std::cout << prompt;
    }
    std::string discardInput;
    std::getline(std::cin, discardInput);
}