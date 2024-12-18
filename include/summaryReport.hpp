#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "declarations.hpp"
#include "utils.hpp"
#include <iostream>

namespace SummaryReport {
    float ComputeACC(const GridData &coverageGrid, const std::vector<Vec2D> &cityPositions) {
        return 0;
    }

    float ComputeAP(const GridData &pressureGrid, const std::vector<Vec2D> &cityPositions) {
        return 0;
    }

    float ComputeRainProbability(const char AP_LMH, const char ACC_LMH) {
        return 0;
    }

    void PrintAscii(const float rainProbability) {
        std::cout << "TODO: Print ASCII Graphics" << std::endl;
    }

    std::vector<Vec2D> WithExpandedPerimeter(const std::vector<Vec2D> &positionVec) {
        std::set<Vec2D> positionSet = Utils::VectorToSet(positionVec);
        for (const Vec2D &pos : positionSet) {
            for (const Vec2D &dir : ALL_DIRECTIONS) {
                positionSet.insert(Vec2D(pos.x + dir.x, pos.y + dir.y));
            }
        }
        return Utils::SetToVector(positionSet);
    }

    std::map<CityID, std::vector<Vec2D>> GetAllCityPositions(const GridData &cityGrid) {
        std::map<CityID, std::vector<Vec2D>> allCityPositions;
        const int width = (cityGrid.topRight.x - cityGrid.bottomLeft.x) + 1;
        const int height = (cityGrid.topRight.y - cityGrid.bottomLeft.y) + 1;
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                const int cityID = cityGrid.arr[x][y];
                if (cityID != 0) {
                    allCityPositions[cityID].emplace_back(Vec2D(x, y));
                }
            }
        }
        return allCityPositions;
    }

    void GenerateSummaryReport(const std::map<GRID_TYPE, GridData> &allGrids, const std::map<CityID, std::string> &cityLookupTable) {
        std::cout << "Weather Forecast Summary Report" << std::endl;
        std::cout << "-------------------------------" << std::endl;
        const std::map<CityID, std::vector<Vec2D>> allCityPositions = GetAllCityPositions(allGrids.at(GRID_TYPE::CITY));
        for (const auto &data : allCityPositions) {
            const CityID cityID = data.first;
            const std::vector<Vec2D> &cityPositions = data.second;
            const GridData &cloudCoverageGrid = allGrids.at(GRID_TYPE::COVERAGE);
            const GridData &atmosPressureGrid= allGrids.at(GRID_TYPE::COVERAGE);

            const float avgCloudCover = ComputeACC(cloudCoverageGrid, cityPositions);
            const float avgPressure = ComputeAP(atmosPressureGrid, cityPositions);
            // TODO: Extract conversion of values to LMH
            // const float rainProbability = ComputeRainProbability();

            std::cout << "City Name: " << cityLookupTable.at(cityID) << std::endl;
            std::cout << "City ID: " << cityID << std::endl;
            std::cout << "Ave. Cloud Cover (ACC): " << avgCloudCover << std::endl;
            std::cout << "Ave. Pressure (AP): " << avgPressure << std::endl;
            // std::cout << "Pro"
            Utils::PrintNewlines(2);
        }
    }
} // namespace SummaryReport

#endif