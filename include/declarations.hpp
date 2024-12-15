#ifndef DECLARATIONS_H
#define DECLARATIONS_H

#include <map>
#include <string>
#include <vector>

/*
 * Generic Data Containers
 */
struct Pos2D {
    int x, y;
    Pos2D(const int _x, const int _y) : x(_x), y(_y) {}
};

enum class GRID_TYPE {
    CITY,
    COVERAGE,
    PRESSURE
};

struct Grid {
    const Pos2D min;
    const int width, height;
    int **data;

    Grid(const Pos2D _min, const int _width, const int _height)
        : min(_min), width(_width), height(_height) {}
};

struct Range {
    const int min, max;
    Range(const int _min, const int _max)
        : min(_min), max(_max) {}
};

struct ConfigData {
    const Range gridRangeX;
    const Range gridRangeY;
    const std::vector<std::string> cityLocations;
    const std::vector<std::string> cloudCover;
    const std::vector<std::string> pressure;

    ConfigData(
        const Range _gridRangeX, const Range _gridRangeY,
        const std::vector<std::string> &_cityLocations,
        const std::vector<std::string> &_cloudCover,
        const std::vector<std::string> &_pressure)
        : gridRangeX(_gridRangeX), gridRangeY(_gridRangeY),
          cityLocations(_cityLocations), cloudCover(_cloudCover), pressure(_pressure) {}
};

/*
 * 'Status' return type declarations
 *
 * A common convention you will see used throughout the application is a function returning a SomeStatus
 * These structs just bundle a 'bool status' with whatever is being returned - so that the caller can check the 'status' or 'success' of the return
 */
struct ReadFileStatus {
    const bool status;
    const std::vector<std::string> allLines;

    ReadFileStatus(
        const bool _status,
        const std::vector<std::string> _allLines = {})
        : status(_status), allLines(_allLines) {}
};

struct InputData {
    const bool isValid;
    const int numChoice;

    InputData(
        const bool _isValid, const int _numChoice = -1)
        : isValid(_isValid), numChoice(_numChoice) {}
};

/*
 * Miscellaneous
 */
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

#endif