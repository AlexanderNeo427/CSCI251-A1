#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <cmath>
#include <map>
#include <string>
#include <vector>

using CityID = int;
// using iPos2D = std::tuple<int, int>;

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
    PROCESS_CONFIG_FILE = 1,
    DISPLAY_CITY_MAP = 2,
    COVERAGE_MAP_IDX = 3,
    COVERAGE_MAP_LMH = 4,
    ATMOS_PRESSURE_IDX = 5,
    ATMOS_PRESSURE_LMH = 6,
    SUMMARY_REPORT = 7,
    QUIT = 8
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

struct Vec2D final {
    int x, y;
    Vec2D() : x(0), y(0) {}
    Vec2D(const int _x, const int _y) : x(_x), y(_y) {}

    bool operator==(const Vec2D &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    struct Hash {
        std::size_t operator()(const Vec2D &vec) const {
            return std::hash<int>()(vec.x) ^ (std::hash<int>()(vec.y) << 1);
        }
    };
};

struct GridData final {
    int **arr;
    Vec2D bottomLeft, topRight;
};

struct ConfigData final {
    Vec2D bottomLeft, topRight;
    std::vector<std::string> cityLocations, cloudCoverages, atmosPressures;
};

/*
 * 'Status' return type declarations
 *
 * A common convention you will see used throughout the application is a function returning a SomeStatus
 * These structs just bundle a 'bool status' with whatever is being returned - so that the caller can check the 'status' or 'success' of the return
 */
struct GenericStatus final {
    const bool status;
    const std::string message;

    GenericStatus(const bool _status, const std::string &_message = "")
        : status(_status), message(_message) {}
};

struct ReadFileStatus final {
    const bool status;
    const std::vector<std::string> allLines;

    ReadFileStatus(
        const bool _status,
        const std::vector<std::string> _allLines = {})
        : status(_status), allLines(_allLines) {}
};

struct ConfigDataStatus final {
    const bool status;
    const ConfigData configData;

    ConfigDataStatus(const bool _status, const ConfigData &_configData = {})
        : status(_status), configData(_configData) {}
};

struct InputData final {
    const bool isValid;
    const int numChoice;

    InputData(const bool _isValid, const int _numChoice = -1)
        : isValid(_isValid), numChoice(_numChoice) {}
};

//========================================
//============= Constants ================
//========================================

extern const std::map<MENU_OPTION, std::string> ALL_OPTIONS;
extern const std::vector<Vec2D> ALL_DIRECTIONS;

#endif