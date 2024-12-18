#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <cmath>
#include <map>
#include <string>
#include <vector>

using CityID = int;

enum class CONSOLE_COLOR {
    DEFAULT = 0,
    BLACK = 30,
    RED = 31,
    GREEN = 32,
    YELLOW = 33,
    BLUE = 34,
    MAGENTA = 35,
    CYAN = 36,
    WHITE = 37,
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

enum class RENDER_MODE {
    CITY,
    INDEX,
    LMH,
};

enum class GRID_TYPE {
    CITY,
    COVERAGE,
    PRESSURE
};

struct Vec2D {
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

struct GridData {
    int **arr;
    Vec2D bottomLeft, topRight;
};

struct ConfigData {
    Vec2D bottomLeft, topRight;
    std::vector<std::string> cityLocations, cloudCoverages, atmosPressures;
};

/*
 * 'Status' return type declarations
 *
 * A common convention you will see used throughout the application is a function returning a SomeStatus
 * These structs just bundle a 'bool status' with whatever is being returned - so that the caller can check the 'status' or 'success' of the return
 */
struct GenericStatus {
    const bool status;
    const std::string message;

    GenericStatus(const bool _status, const std::string &_message = "")
        : status(_status), message(_message) {}
};

struct ReadFileStatus {
    const bool status;
    const std::vector<std::string> allLines;

    ReadFileStatus(
        const bool _status,
        const std::vector<std::string> _allLines = {})
        : status(_status), allLines(_allLines) {}
};

struct ConfigDataStatus {
    const bool status;
    const ConfigData configData;

    ConfigDataStatus(const bool _status, const ConfigData &_configData = {})
        : status(_status), configData(_configData) {}
};

struct InputData {
    const bool isValid;
    const int numChoice;

    InputData(const bool _isValid, const int _numChoice = -1)
        : isValid(_isValid), numChoice(_numChoice) {}
};

//========================================
//============= Constants ================
//========================================

const std::map<OPTION, std::string> ALL_OPTIONS{
    {OPTION::PROCESS_CONFIG_FILE, "Read in and process a configuration file"},
    {OPTION::DISPLAY_CITY_MAP, "Display city map"},
    {OPTION::COVERAGE_MAP_IDX, "Display cloud coverage map (cloudiness index)"},
    {OPTION::COVERAGE_MAP_LMH, "Display cloud coverage map (LMH symbols)"},
    {OPTION::ATMOS_PRESSURE_IDX, "Display atmospheric pressure map (pressure index)"},
    {OPTION::ATMOS_PRESSURE_LMH, "Display atmospheric pressure map (LMH symbols)"},
    {OPTION::SUMMARY_REPORT, "Show weather forecast summary report"},
    {OPTION::QUIT, "Quit"},
};

const std::vector<Vec2D> ALL_DIRECTIONS{
    Vec2D(-1, -1), // Bottom-Left
    Vec2D(-1, 0),  // Left
    Vec2D(-1, 1),  // Left-Top
    Vec2D(0, 1),   // Top
    Vec2D(1, 1),   // Right-Top
    Vec2D(1, 0),   // Right
    Vec2D(1, -1),  // Right-Bottom
    Vec2D(0, -1),  // Bottom
};

#endif