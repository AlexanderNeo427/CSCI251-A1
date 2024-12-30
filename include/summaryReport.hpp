#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "declarations.hpp"
#include "utils.hpp"
#include <iostream>

namespace SummaryReport {
    std::vector<Vec2D> WithSurroundingGridArea(const std::vector<Vec2D> &posVec, const Vec2D &bottomLeft, const Vec2D &topRight) {
        std::unordered_set<Vec2D, Vec2D::Hash> posSet = Utils::VectorToSet(posVec);
        for (const Vec2D &pos : posVec) {
            for (const Vec2D &dir : ALL_DIRECTIONS) {
                auto nextPos = Vec2D(pos.x + dir.x, pos.y + dir.y);
                nextPos.x = std::max(bottomLeft.x, std::min(topRight.x, nextPos.x));
                nextPos.y = std::max(bottomLeft.y, std::min(topRight.y, nextPos.y));
                posSet.insert(nextPos);
            }
        }
        return Utils::SetToVector(posSet);
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
        Utils::SetConsoleColor(ANSI_4::CYAN);
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

    /**
     * @param allGrids Read-only reference
     * @param cityLookupTable Read-only reference 
     */
    void GenerateSummaryReport(const std::map<GRID_TYPE, GridData> &allGrids, const std::map<CityID, std::string> &cityLookupTable) {
        std::cout << "Weather Forecast Summary Report" << std::endl;
        std::cout << "-------------------------------" << std::endl;

        const GridData &cityGridData = allGrids.at(GRID_TYPE::CITY);
        const std::map<CityID, std::vector<Vec2D>> allCityPositions = GetAllCityPositions(cityGridData);

        for (const auto &data : allCityPositions) {
            const CityID cityID = data.first;
            const std::vector<Vec2D> &cityPositions = data.second;
            const std::vector<Vec2D> &positionsToAggregate = WithSurroundingGridArea(
                cityPositions, cityGridData.bottomLeft, cityGridData.topRight
            );

            const GridData &cloudCoverageGrid = allGrids.at(GRID_TYPE::COVERAGE);
            const float avgCloudCover = ComputeGridAverage(cloudCoverageGrid, positionsToAggregate);
            const char coverageLMH = Utils::GetLMH(avgCloudCover);

            const GridData &atmosPressureGrid = allGrids.at(GRID_TYPE::PRESSURE);
            const float avgPressure = ComputeGridAverage(atmosPressureGrid, positionsToAggregate);
            const char pressureLMH = Utils::GetLMH(avgPressure);

            const int rainProbability = ComputeRainProbability(pressureLMH, coverageLMH);

            Utils::ResetConsoleColor();
            std::cout << "City Name: " << cityLookupTable.at(cityID) << std::endl;
            std::cout << "City ID: " << cityID << std::endl;
            std::cout << "Ave. Cloud Cover (ACC): " << avgCloudCover << " (" << coverageLMH << ")" << std::endl;
            std::cout << "Ave. Pressure (AP): " << avgPressure << " (" << pressureLMH << ")" << std::endl;
            std::cout << "Probability of Rain (%): " << std::to_string(rainProbability) << ".00" << std::endl;
            PrintAscii(pressureLMH, coverageLMH);
            std::cout << std::endl;
        }
    }
} // namespace SummaryReport

#endif