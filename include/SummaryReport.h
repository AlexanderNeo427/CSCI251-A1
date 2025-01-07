#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "Declarations.h"

namespace SummaryReport {
    void GenerateSummaryReport(const GridData &gridData);

    /**
     * @param cityBounds City Boundary in 'grid space'
     * @param gridBounds Grid Boundary in 'grid space'
     */
    Boundary ExpandedBoundary(const Boundary &cityBounds, const Boundary &gridBounds);

    /**
     * @param cityData
     * @param gridBounds Boundary of the entire grid, in 'grid space'
     * @param cityID
     */
    Boundary GetCityBounds(int **const cityData, const Boundary &gridBounds, const CityID cityID);

    /**
     * @param areaToAverage Boundary (in 'grid space') of the grid area to average over
     * @param gridBounds Boundary (in 'grid space') of the entire grid area
     */
    double ComputeGridAverage(int **const data, const Boundary &areaToAverage, const Boundary &gridBounds);
    void PrintAscii(const char avgPressureLMH, const char avgCoverageLMH);
    int ComputeRainProbability(const char avgPressureLMH, const char avgCoverageLMH);
    char GetLMH(const int val);
}; // namespace SummaryReport

#endif