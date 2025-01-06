#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "Declarations.h"
#include <string>

namespace DataLoader {
    bool ParseFile(const std::string &filePath, GridData &gridData, std::string &parseFailReason);
    bool ExtractGridRange(const std::string &rangeLine, GridData &gridData, bool &isRangeX, std::string &extractFailReason);
    bool ReadCityTextFile(const std::string &filePath, GridData &gridData, std::string &readFailReason);
    bool ExtractCityDataLine(const std::string &cityLine, GridData &gridData, std::string &extractFailReason);
} // namespace DataLoader

#endif