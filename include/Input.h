#ifndef INPUT_H
#define INPUT_H

#include <string>

namespace Input {
    bool AwaitStrInput(std::string &strInput, std::string &message, const std::string &prompt = "");
    bool AwaitCharInput(char &charInput, std::string &message, const std::string &prompt = "");
    bool AwaitIntInput(int &intInput, std::string &message, const std::string &prompt = "");
}; // namespace Input

#endif