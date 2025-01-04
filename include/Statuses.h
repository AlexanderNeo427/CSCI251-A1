#ifndef STATUSES_H
#define STATUSES_H

#include <string>

struct StrInputStatus final {
    std::string input;
    std::string message; 
    bool success;
};

struct CharInputStatus final {
    char input;
    std::string message;
    bool success;
};

struct IntInputStatus final {
    int input;
    std::string message;
    bool success;
};

#endif