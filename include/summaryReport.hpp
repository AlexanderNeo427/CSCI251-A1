#ifndef SUMMARY_REPORT_H
#define SUMMARY_REPORT_H

#include "declarations.hpp"

namespace SummaryReport {
    void GenerateSummaryReport(const std::map<GRID_TYPE, GridData>& allGrids) {
    }

    std::map<int, std::vector<Pos2D>> GetCities() {
    }

    std::vector<Pos2D> GetSurrounding(const int cityID) {
    }

    float ComputeACC(const GridData& coverageGrid) {
    } 

    float ComputeAP(const GridData& pressureGrid) {
    }
} // namespace SummaryReport

#endif