#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <array>
#include <string>
#include <utility>

using CityID = int;
const int MAX_CITY_ID = 9;

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

struct Vec2D {
    int x = 0, y = 0;
};

struct GridData {
    // [0] = ""
    // [1] = "Small_city"
    // [2] = "Medium_city"
    // [3] = "Big_city"
    // [4] = ""
    // etc.....
    std::array<std::string, MAX_CITY_ID> cityNames;

    bool isDataInitialized = false;
    Vec2D bottomLeft, topRight;
    int **cityGrid = nullptr;
    int **cloudGrid = nullptr;
    int **pressureGrid = nullptr;
};

#endif