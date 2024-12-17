#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "declarations.hpp"
#include <iostream>

// The calculations are all done with the assumption that the cities are squares
namespace SummaryReport {
    void GenerateSummaryReport(const std::map<GRID_TYPE, GridData> &allGrids) {
        std::cout << "Weather Forecast Summary Report" << std::endl;
        std::cout << "-------------------------------" << std::endl;
    }

    std::map<CityID, std::vector<Pos2D>> GetCitiesPositions(const GridData &cityGrid) {
        std::map<CityID, std::vector<Pos2D>> cities;

        const int width = (cityGrid.rangeX.max - cityGrid.rangeX.min) + 1;
        const int height = (cityGrid.rangeY.max - cityGrid.rangeY.min) + 1;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                const int cityID = cityGrid.arr[x][y];
                if (cityID != 0) {
                    cities[cityID].emplace_back(Pos2D(x, y));
                }
            }
        }
        return cities;
    }

    // I'm assuming that the cities are squares
    std::vector<Pos2D> AppendSurroundingArea(
        const std::map<CityID, std::vector<Pos2D>> &cities,
        const CityID cityID, const Range rangeX, const Range rangeY) {

        const std::vector<Pos2D> &cityPositions = cities.at(cityID);
        auto [bottomLeft, topRight] = GetBoundary(cityPositions);
        bottomLeft.x = std::max(bottomLeft.x - 1, 0);
        bottomLeft.y = std::max(bottomLeft.y - 1, 0);
        // TODO
        // topRight.x = std::min()
    }

    std::tuple<Pos2D, Pos2D> GetBoundary(const std::vector<Pos2D> &cityPositions) {
        auto min = Pos2D(9999, 9999);
        auto max = Pos2D(-9999, -9999);
        for (const Pos2D cityPos : cityPositions) {
            min.x = std::min(min.x, cityPos.x);
            min.y = std::min(min.y, cityPos.y);
            max.x = std::max(max.x, cityPos.x);
            max.y = std::max(max.y, cityPos.y);
        }
        return std::make_tuple(min, max);
    }

    float ComputeACC(const GridData &coverageGrid, const Pos2D bottomLeft, const Pos2D topRight) {
    }

    float ComputeAP(const GridData &pressureGrid, const Pos2D bottomLeft, const Pos2D topRight) {
    }

    float ComputeRainProbability(const char AP_LMH, const char ACC_LMH) {
    }

    void PrintAscii(const float rainProbability) {
    }
} // namespace SummaryReport

#endif