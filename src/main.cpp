#include "Declarations.h"
#include "WeatherApp.h"
#include <iostream>

int main() {
    while (true) {
        std::cout << ANSI::DEFAULT;
        WeatherApp::PrintMainMenu();
        break;
    }
    // Cleanup
    // for (const std::pair<const GRID_TYPE, GridData> &grid : allGrids) {
    //     GridData data = grid.second;
    //     const int width = (data.topRight.x - data.bottomLeft.x) + 1;
    //     for (int x = 0; x < width; x++) {
    //         delete[] data.arr[x];
    //         data.arr[x] = nullptr;
    //     }
    //     delete[] data.arr;
    //     data.arr = nullptr;
    // }
    return EXIT_SUCCESS;
};
