#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <map>
#include <string>

struct iVec2D {
    int x, y;
    iVec2D(const int _x, const int _y) : x(_x), y(_y) {}
};

struct Grid {
    iVec2D min;
    const int width, height;
};

struct InputStatus {
    const bool status;
    const std::string userInput;

    InputStatus(
        const bool _status, const std::string &_user_input = "")
        : status(_status), userInput(_user_input) {}
};

struct ChoiceStatus {
    const bool status;
    const int choice;

    ChoiceStatus(
        const bool _status, const int _choice = -1)
        : status(_status), choice(_choice) {}
};

enum class OPTION {
    PROCESS_CONFIG_FILE = 1,
    DISPLAY_CITY_MAP = 2,
    COVERAGE_MAP_IDX = 3,
    COVERAGE_MAP_LMH = 4,
    ATMOS_PRESSURE_IDX = 5,
    ATMOS_PRESSURE_LMH = 6,
    SUMMARY_REPORT = 7,
    QUIT = 8
};

const std::map<OPTION, std::string> allOptions{
    {OPTION::PROCESS_CONFIG_FILE, "Read in and process a configuration file"},
    {OPTION::DISPLAY_CITY_MAP, "Display city map"},
    {OPTION::COVERAGE_MAP_IDX, "Display cloud coverage map (cloudiness index)"},
    {OPTION::COVERAGE_MAP_LMH, "Display cloud coverage map (LMH symbols)"},
    {OPTION::ATMOS_PRESSURE_IDX, "Display atmospheric pressure map (pressure index)"},
    {OPTION::ATMOS_PRESSURE_LMH, "Display atmospheric pressure map (LMH symbols)"},
    {OPTION::SUMMARY_REPORT, "Show weather forecast summary report"},
    {OPTION::QUIT, "Quit"},
};

#endif