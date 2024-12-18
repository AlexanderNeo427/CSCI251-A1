#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "declarations.hpp"
#include "utils.hpp"
#include <algorithm>
#include <iostream>

namespace SummaryReport {
    std::vector<Vec2D> WithSurroundingGridArea(const std::vector<Vec2D> &positionVec, const Vec2D &bottomLeft, const Vec2D &topRight) {
        std::cout << "Calc surround grid area, boundaries: " << std::endl;
        std::cout << "Min: " << bottomLeft.x << ", " << bottomLeft.y << std::endl;
        std::cout << "Max: " << topRight.x << ", " << topRight.y << std::endl;

        std::set<Vec2D> positionSet = Utils::VectorToSet(positionVec);
        for (const Vec2D &pos : positionVec) {
            for (const Vec2D &dir : ALL_DIRECTIONS) {
                auto nextPos = Vec2D(pos.x + dir.x, pos.y + dir.y);
                nextPos.x = std::max(bottomLeft.x, std::min(topRight.x, nextPos.x));
                nextPos.y = std::max(bottomLeft.y, std::min(topRight.y, nextPos.y));
                positionSet.insert(nextPos);
            }
        }
        return Utils::SetToVector(positionSet);
    }

    float ComputeGridAverage(const GridData &gridData, const std::vector<Vec2D> &positions) {
        float sum = 0;
        for (const Vec2D &pos : positions) {
            const float gridValue = static_cast<float>(gridData.arr[pos.x][pos.y]);
            sum += gridValue;
        }
        return sum / static_cast<float>(positions.size());
    }

    void PrintAscii(const char avgPressureLMH, const char avgCoverageLMH) {
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
    }

    int ComputeRainProbability(const char avgPressureLMH, const char avgCoverageLMH) {
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
                return 50;
            } else if (avgCoverageLMH == 'M') {
                return 40;
            } else if (avgCoverageLMH == 'L') {
                return 30;
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

        const GridData &cityGridData = allGrids.at(GRID_TYPE::CITY);
        const std::map<CityID, std::vector<Vec2D>> allCityPositions = GetAllCityPositions(cityGridData);

        std::set<Vec2D> mySet;
        mySet.insert(Vec2D(1, 2));
        mySet.insert(Vec2D(1, 2));
        mySet.insert(Vec2D(2, 1));
        mySet.insert(Vec2D(3, 1));
        for (const auto &pos : mySet) {
            std::cout << pos.x << ", " << pos.y << std::endl;
        }

        // for (const auto &data : allCityPositions) {
        //     const CityID cityID = data.first;
        //     const std::vector<Vec2D> &cityPositions = data.second;
        //     const std::vector<Vec2D> &positionsToAggregate = WithSurroundingGridArea(
        //         cityPositions, cityGridData.bottomLeft, cityGridData.topRight);

        //     // DEBUG
        //     // std::cout << "City ID: " << cityID << std::endl;
        //     // std::cout << "City Name: " << cityLookupTable.at(cityID) << std::endl
        //     //           << std::endl;

        //     // std::cout << "City Positions: " << std::endl;
        //     // for (const Vec2D &pos : cityPositions) {
        //     //     std::cout << pos.x << ", " << pos.y << std::endl;
        //     // }
        //     // std::cout << "==================" << std::endl;

        //     // std::cout << "Positions to aggregate: " << std::endl;
        //     // for (const Vec2D &pos : positionsToAggregate) {
        //     //     std::cout << pos.x << ", " << pos.y << std::endl;
        //     // }

        //     // const GridData &cloudCoverageGrid = allGrids.at(GRID_TYPE::COVERAGE);
        //     // const float avgCloudCover = ComputeGridAverage(cloudCoverageGrid, positionsToAggregate);
        //     // const char coverageLMH = Utils::GetLMH(avgCloudCover);

        //     // const GridData &atmosPressureGrid = allGrids.at(GRID_TYPE::PRESSURE);
        //     // const float avgPressure = ComputeGridAverage(atmosPressureGrid, positionsToAggregate);
        //     // const char pressureLMH = Utils::GetLMH(avgPressure);

        //     // const int rainProbability = ComputeRainProbability(pressureLMH, coverageLMH);

        //     // std::cout << "City Name: " << cityLookupTable.at(cityID) << std::endl;
        //     // std::cout << "City ID: " << cityID << std::endl;
        //     // std::cout << "Ave. Cloud Cover (ACC): " << avgCloudCover << "(" << coverageLMH << ")" << std::endl;
        //     // std::cout << "Ave. Pressure (AP): " << avgPressure << "(" << pressureLMH << ")" << std::endl;
        //     // std::cout << "Probability of Rain (%): " << std::to_string(rainProbability) << ".00" << std::endl;
        //     // PrintAscii(pressureLMH, coverageLMH);
        //     // Utils::PrintNewlines(2);
        // }
    }
} // namespace SummaryReport

#endif