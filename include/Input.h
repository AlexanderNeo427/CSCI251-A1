#ifndef INPUT_H
#define INPUT_H

#include "Statuses.h"

namespace Input {
    StrInputStatus AwaitStrInput(const std::string &prompt = "");
    CharInputStatus AwaitCharInput(const std::string &prompt = "");
    IntInputStatus AwaitIntInput(const std::string &prompt = "");
    void AwaitEnterInput(const std::string &prompt = "\nPress enter to continue....");
}; // namespace Input

#endif