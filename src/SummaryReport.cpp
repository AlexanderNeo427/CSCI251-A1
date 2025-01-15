#include "SummaryReport.h"
#include <iomanip>
#include <iostream>

void SummaryReport::GenerateSummaryReport(const GridData &gridData) {
    Boundary gridBoundary;
    gridBoundary.min = gridData.bottomLeft;
    gridBoundary.max = gridData.topRight;

    std::cout << ANSI::DEFAULT;
    std::cout << "Weather Forecast Summary Report" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    for (CityID cityID = CITY_ID_COUNT - 1; cityID >= 0; cityID--) {
        const std::string cityName = gridData.cityNames[cityID];
        if (cityName.empty()) {
            continue;
        }

        { // City Data (Name, ID)
            const int cityDataWidth = std::string("City Name: ").length();
            std::cout << ANSI::GREEN << std::setw(cityDataWidth) << std::left << "City Name: ";
            std::cout << ANSI::DEFAULT << cityName << std::endl;

            std::cout << ANSI::GREEN << std::setw(cityDataWidth) << std::left << "City ID: ";
            std::cout << ANSI::DEFAULT << cityID << std::endl;
        }

        { // Weather Data (Cloud cover, pressure, probability of rain)
            const int weatherDataWidth = std::string("Probability of Rain (%): ").length();
            const Boundary cityBounds = SummaryReport::GetCityBounds(gridData.cityGrid, gridBoundary, cityID);
            const Boundary expandedBoundary = SummaryReport::ExpandedBoundary(cityBounds, gridBoundary);

            std::cout << ANSI::YELLOW << std::setw(weatherDataWidth) << std::left << "Ave. Cloud Cover (ACC): ";

            const double avgCloudCover = SummaryReport::ComputeGridAverage(gridData.cloudGrid, expandedBoundary, gridBoundary);

            const char cloudCoverLMH = SummaryReport::GetLMH(avgCloudCover);
            std::cout << ANSI::DEFAULT << std::fixed << std::setprecision(2) << std::setw(4) << avgCloudCover;
            std::cout << " (" << cloudCoverLMH << ")" << std::endl;

            std::cout << ANSI::YELLOW << std::setw(weatherDataWidth) << std::left << "Ave. Pressure (AP): ";

            const double avgPressure = SummaryReport::ComputeGridAverage(gridData.pressureGrid, expandedBoundary, gridBoundary);

            const char pressureLMH = SummaryReport::GetLMH(avgPressure);
            std::cout << ANSI::DEFAULT << std::fixed << std::setprecision(2) << std::setw(4) << avgPressure;
            std::cout << " (" << pressureLMH << ")" << std::endl;

            std::cout << ANSI::CYAN << std::setw(weatherDataWidth) << std::left << "Probability of Rain (%): ";
            const double rainProbability = SummaryReport::ComputeRainProbability(pressureLMH, cloudCoverLMH);
            std::cout << ANSI::DEFAULT << std::fixed << std::setprecision(2) << rainProbability << std::endl;

            SummaryReport::PrintAscii(pressureLMH, cloudCoverLMH);
            std::cout << std::endl;
        }
    }
}

Boundary SummaryReport::ExpandedBoundary(const Boundary &cityBounds, const Boundary &gridBounds) {
    Boundary newCityBounds;
    newCityBounds.min.x = std::max(cityBounds.min.x - 1, gridBounds.min.x);
    newCityBounds.min.y = std::max(cityBounds.min.y - 1, gridBounds.min.y);
    newCityBounds.max.x = std::min(cityBounds.max.x + 1, gridBounds.max.x);
    newCityBounds.max.y = std::min(cityBounds.max.y + 1, gridBounds.max.y);
    return newCityBounds;
}

Boundary SummaryReport::GetCityBounds(int **const cityData, const Boundary &gridBounds, const CityID cityID) {
    const int rangeX = (gridBounds.max.x - gridBounds.min.x) + 1;
    const int rangeY = (gridBounds.max.y - gridBounds.min.y) + 1;

    Boundary cityBounds;
    cityBounds.min.x = 999999;
    cityBounds.min.y = 999999;
    cityBounds.max.x = -999999;
    cityBounds.max.x = -999999;
    for (int x_arrSpace = 0; x_arrSpace < rangeX; x_arrSpace++) {
        for (int y_arrSpace = 0; y_arrSpace < rangeY; y_arrSpace++) {
            if (cityData[x_arrSpace][y_arrSpace] == cityID) {
                const int x_gridSpace = x_arrSpace + gridBounds.min.x;
                const int y_gridSpace = y_arrSpace + gridBounds.min.y;
                cityBounds.min.x = std::min(cityBounds.min.x, x_gridSpace);
                cityBounds.min.y = std::min(cityBounds.min.y, y_gridSpace);
                cityBounds.max.x = std::max(cityBounds.max.x, x_gridSpace);
                cityBounds.max.y = std::max(cityBounds.max.y, y_gridSpace);
            }
        }
    }
    return cityBounds;
}

double SummaryReport::ComputeGridAverage(int **const data, const Boundary &areaToAverage, const Boundary &gridBounds) {
    double sum = 0;
    int numValues = 0;
    for (int y_gridSpace = areaToAverage.max.y; y_gridSpace >= areaToAverage.min.y; y_gridSpace--) {
        for (int x_gridSpace = areaToAverage.min.x; x_gridSpace <= areaToAverage.max.x; x_gridSpace++) {
            const int x_arrSpace = x_gridSpace - gridBounds.min.x;
            const int y_arrSpace = y_gridSpace - gridBounds.min.y;
            sum += data[x_arrSpace][y_arrSpace];
            numValues++;
        }
    }
    return sum / numValues;
}

void SummaryReport::PrintAscii(const char avgPressureLMH, const char avgCoverageLMH) {
    std::cout << ANSI::CYAN;
    if (avgPressureLMH == 'L') {
        if (avgCoverageLMH == 'H') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << "\\\\\\\\\\" << std::endl;
        } else if (avgCoverageLMH == 'M') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << " \\\\\\\\" << std::endl;
        } else if (avgCoverageLMH == 'L') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << "   \\\\\\" << std::endl;
        }
    } else if (avgPressureLMH == 'M') {
        if (avgCoverageLMH == 'H') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << "   \\\\" << std::endl;
        } else if (avgCoverageLMH == 'M') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << "    \\" << std::endl;
        } else if (avgCoverageLMH == 'L') {
            std::cout << "~~~~" << std::endl;
            std::cout << "~~~~~" << std::endl;
            std::cout << std::endl;
        }
    } else if (avgPressureLMH == 'H') {
        if (avgCoverageLMH == 'H') {
            std::cout << "~~~" << std::endl;
            std::cout << "~~~~" << std::endl;
            std::cout << std::endl;
        } else if (avgCoverageLMH == 'M') {
            std::cout << "~~" << std::endl;
            std::cout << "~~~" << std::endl;
            std::cout << std::endl;
        } else if (avgCoverageLMH == 'L') {
            std::cout << "~" << std::endl;
            std::cout << "~~" << std::endl;
            std::cout << std::endl;
        }
    }
    std::cout << ANSI::DEFAULT;
}

int SummaryReport::ComputeRainProbability(const char avgPressureLMH, const char avgCoverageLMH) {
    if (avgPressureLMH == 'L') {
        if (avgCoverageLMH == 'H') {
            return 90;
        } else if (avgCoverageLMH == 'M') {
            return 80;
        } else if (avgCoverageLMH == 'L') {
            return 70;
        }
    } else if (avgPressureLMH == 'M') {
        if (avgCoverageLMH == 'H') {
            return 60;
        } else if (avgCoverageLMH == 'M') {
            return 50;
        } else if (avgCoverageLMH == 'L') {
            return 40;
        }
    } else if (avgPressureLMH == 'H') {
        if (avgCoverageLMH == 'H') {
            return 30;
        } else if (avgCoverageLMH == 'M') {
            return 20;
        } else if (avgCoverageLMH == 'L') {
            return 10;
        }
    }
    return -1;
}

char SummaryReport::GetLMH(const int val) {
    if (val >= 0 && val < 35) {
        return 'L';
    } else if (val >= 35 && val < 65) {
        return 'M';
    } else if (val >= 65 && val < 100) {
        return 'H';
    }
    return '-';
}
