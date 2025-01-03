#include "Declarations.hpp"

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
