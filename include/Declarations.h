#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <string>
#include <utility>

using CityID = int;

namespace ANSI {
    using Color = std::string;

    const ANSI::Color DEFAULT = "\033[0m";
    const ANSI::Color RED = "\033[31m";
    const ANSI::Color GREEN = "\033[32m";
    const ANSI::Color YELLOW = "\033[33m";
    const ANSI::Color BLUE = "\033[34m";
    const ANSI::Color CYAN = "\033[36m";
    const ANSI::Color WHITE = "\033[37m";
}; // namespace ANSI

enum class MENU_OPTION : unsigned int {
    PROCESS_CONFIG_FILE,
    DISPLAY_CITY_MAP,
    COVERAGE_MAP_IDX,
    COVERAGE_MAP_LMH,
    ATMOS_PRESSURE_IDX,
    ATMOS_PRESSURE_LMH,
    SUMMARY_REPORT,
    QUIT,

    ENTRY_COUNT,
};

// const std::pair<MENU_OPTION, std::string> data{
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::DISPLAY_CITY_MAP, ""),
//     std::make_pair(MENU_OPTION::COVERAGE_MAP_IDX, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
//     std::make_pair(MENU_OPTION::PROCESS_CONFIG_FILE, ""),
// };

enum class RENDER_MODE : unsigned int {
    CITY,
    INDEX,
    LMH,
};

enum class GRID_TYPE : unsigned int {
    CITY,
    COVERAGE,
    PRESSURE
};

#endif