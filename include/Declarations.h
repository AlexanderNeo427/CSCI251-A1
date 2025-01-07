#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <array>
#include <string>
#include <utility>

using CityID = int;
const int CITY_ID_COUNT = 100;

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

const std::array<ANSI::Color, 10> INDEX_COLOURS = {
    ANSI::RED,
    ANSI::GREEN,
    ANSI::YELLOW,
    ANSI::BLUE,
    ANSI::CYAN,
    ANSI::RED,
    ANSI::GREEN,
    ANSI::YELLOW,
    ANSI::BLUE,
    ANSI::CYAN,
};

enum class MENU_OPTION : unsigned int {
    PROCESS_CONFIG_FILE,
    DISPLAY_CITY_MAP,
    CLOUD_MAP_IDX,
    CLOUD_MAP_LMH,
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

struct Vec2D {
    int x = 0, y = 0;
};

struct Boundary {
    Vec2D min, max;
};

struct GridData {
    // [0] = ""
    // [1] = "Small_city"
    // [2] = "Medium_city"
    // [3] = "Big_city"
    // [4] = ""
    // etc.....
    std::array<std::string, CITY_ID_COUNT> cityNames;

    bool isDataLoaded;
    Vec2D bottomLeft, topRight;
    int **cityGrid, **cloudGrid, **pressureGrid;

    GridData()
        : cityNames(), isDataLoaded(false),
          bottomLeft(), topRight(),
          cityGrid(nullptr), cloudGrid(nullptr), pressureGrid(nullptr) {}

    GridData(const GridData &rhs)
        : cityNames(rhs.cityNames),
          isDataLoaded(rhs.isDataLoaded),
          bottomLeft(rhs.bottomLeft),
          topRight(rhs.topRight),
          cityGrid(rhs.cityGrid),
          cloudGrid(rhs.cloudGrid),
          pressureGrid(rhs.pressureGrid){};
};

#endif