#include "Renderer.h"
#include "SummaryReport.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>

void Renderer::RenderGrid(
    int **const data,
    std::string *const cityNames,
    const Vec2D &bottomLeft, const Vec2D &topRight,
    const RENDER_MODE renderMode) {

    const int rangeX = (topRight.x - bottomLeft.x) + 1;
    const int rangeY = (topRight.y - bottomLeft.y) + 1;

    int highestCityID = 0;
    for (CityID cityID = 0; cityID < CITY_ID_COUNT; cityID++) {
        if (!cityNames[cityID].empty()) {
            highestCityID = std::max(cityID, highestCityID);
        }
    }

    int xCharWidth = std::max(std::to_string(topRight.x).length(),
                              std::to_string(bottomLeft.x).length()) +
                     1;
    xCharWidth = std::max(
        xCharWidth,
        static_cast<int>(std::to_string(highestCityID).length() + 1));
    const int yCharWidth = std::max(std::to_string(topRight.y).length(),
                                    std::to_string(bottomLeft.y).length()) +
                           1;

    const int leftPad = 3;
    const int wallLength = rangeX + 2;

    const ANSI::Color wallColor = ANSI::DEFAULT;

    // Roof
    std::cout << std::right << std::setw(leftPad + yCharWidth) << ""; // Left-pad
    for (int i = 0; i < wallLength; i++) {
        std::cout << wallColor << std::setw(xCharWidth) << "#";
    }
    std::cout << ANSI::DEFAULT << std::endl;

    // Middle
    for (int y = rangeY - 1; y >= 0; y--) {
        std::cout << std::setw(leftPad) << ""; // Left-pad
        std::cout << std::setw(yCharWidth) << std::right << (y + bottomLeft.y);
        std::cout << wallColor << std::setw(xCharWidth) << "#" << ANSI::DEFAULT;
        for (int x = 0; x < rangeX; x++) {
            const int cellValue = data[x][y];
            const int indexValue = cellValue % 10;
            ANSI::Color indexColor = ANSI::DEFAULT;
            if (indexValue >= 0 && indexValue < static_cast<int>(INDEX_COLOUR_COUNT)) {
                indexColor = INDEX_COLOURS[indexValue];
            }

            switch (renderMode) {
                case RENDER_MODE::CITY: {
                    std::string cityName = "";
                    if (cellValue >= 0 && cellValue < CITY_ID_COUNT) {
                        cityName = cityNames[cellValue];
                    }
                    if (!cityName.empty()) {
                        std::cout << indexColor << std::setw(xCharWidth) << cellValue << ANSI::DEFAULT;
                    } else {
                        std::cout << std::setw(xCharWidth) << "";
                    }
                    break;
                }
                case RENDER_MODE::INDEX: {
                    const int indexValue = static_cast<float>(cellValue) / 10.0f;

                    ANSI::Color indexColor = ANSI::DEFAULT;
                    if (indexValue >= 0 && indexValue < static_cast<int>(INDEX_COLOUR_COUNT)) {
                        indexColor = INDEX_COLOURS[indexValue];
                    }
                    std::cout << indexColor << std::setw(xCharWidth) << indexValue;
                    break;
                }
                case RENDER_MODE::LMH: {
                    const char symbol = SummaryReport::GetLMH(cellValue);
                    ANSI::Color symbolColor = ANSI::DEFAULT;
                    if (symbol == 'L') {
                        symbolColor = ANSI::GREEN;
                    } else if (symbol == 'M') {
                        symbolColor = ANSI::YELLOW;
                    } else if (symbol == 'H') {
                        symbolColor = ANSI::RED;
                    }
                    std::cout << symbolColor << std::setw(xCharWidth) << symbol;
                    break;
                }
                default:
                    break;
            }
        }
        std::cout << wallColor << std::setw(xCharWidth) << "#" << ANSI::DEFAULT << std::endl;
    }

    // Floor
    std::cout << std::setw(leftPad + yCharWidth) << ""; // Left-pad
    for (int i = 0; i < wallLength; i++) {
        std::cout << wallColor << std::setw(xCharWidth) << "#";
    }
    std::cout << ANSI::DEFAULT << std::endl;

    // X-axis coords
    std::cout << std::setw(leftPad + yCharWidth + xCharWidth) << "";
    for (int x = 0; x < rangeX; x++) {
        std::cout << std::setw(xCharWidth) << (x + bottomLeft.x);
    }
    std::cout << std::endl;
}