#ifndef WEATHER_APP_H
#define WEATHER_APP_H

namespace WeatherApp {
    void PrintMainMenu();
    bool AwaitUserInput(int &input);
    // void RenderGrid(const GridData &gridData, const RENDER_MODE renderMode, const unsigned int padAmount = 2);

    // /**
    //  * @param refAllGrids Mutable reference to the grid data
    //  */
    // GenericStatus HandleOption(
    //     const MENU_OPTION option,
    //     std::map<GRID_TYPE, GridData> &refAllGrids,
    //     std::map<CityID, std::string> &refCityLookupTable);
}; // namespace WeatherApp

#endif
