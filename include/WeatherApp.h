#ifndef WEATHER_APP_H
#define WEATHER_APP_H

#include "Declarations.h"

namespace WeatherApp {
    void PrintMainMenu();
    void HandleOption(const MENU_OPTION menuOption, GridData& gridData);
    std::string OptionToText(const MENU_OPTION menuOption);
}; // namespace WeatherApp

#endif
