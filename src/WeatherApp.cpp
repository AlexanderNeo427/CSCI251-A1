#include "WeatherApp.h"
#include "DataLoader.h"
#include "Input.h"
#include "Renderer.h"
#include "Utils.h"
#include <iostream>

void WeatherApp::PrintMainMenu() {
    std::cout << ANSI::BLUE << std::endl;
    std::cout << "Student ID:   9085610" << std::endl;
    std::cout << "Student Name: Alexander Neo" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << ANSI::DEFAULT;
    std::cout << "Welcome to Weather Information Processing System!";
    Utils::PrintNewlines(2);
    const int numOptions = static_cast<int>(MENU_OPTION::ENTRY_COUNT);
    for (int i = 0; i < numOptions; i++) {
        const MENU_OPTION menuOption = static_cast<MENU_OPTION>(i);
        std::cout << (i + 1) << ")\t" << WeatherApp::OptionToText(menuOption) << std::endl;
    }
    std::cout << std::endl;
};

void WeatherApp::HandleOption(const MENU_OPTION menuOption, GridData &gridData) {
    switch (menuOption) {
        case MENU_OPTION::PROCESS_CONFIG_FILE: {
            const std::string fileName = "./data/config.txt";

            std::string failReason = "";
            const bool parseSuccess = DataLoader::ParseFile(fileName, gridData, failReason);

            if (!parseSuccess) {
                std::cerr << failReason << std::endl;
                break;
            }
            std::cout << "All records successfully stored. Going back to main menu..." << std::endl;
            break;
        }
        case MENU_OPTION::DISPLAY_CITY_MAP: {
            Renderer::RenderGrid(gridData.cityGrid, gridData.bottomLeft, gridData.topRight, RENDER_MODE::CITY);
            break;
        }
        case MENU_OPTION::COVERAGE_MAP_IDX: {
            break;
        }
        case MENU_OPTION::COVERAGE_MAP_LMH: {
            break;
        }
        case MENU_OPTION::ATMOS_PRESSURE_IDX: {
            break;
        }
        case MENU_OPTION::ATMOS_PRESSURE_LMH: {
            break;
        }
        case MENU_OPTION::SUMMARY_REPORT: {
            break;
        }
        default:
            break;
    }
}

std::string WeatherApp::OptionToText(const MENU_OPTION menuOption) {
    switch (menuOption) {
        case MENU_OPTION::PROCESS_CONFIG_FILE:
            return "Read in and process a configuration file";
        case MENU_OPTION::DISPLAY_CITY_MAP:
            return "Display city map";
        case MENU_OPTION::COVERAGE_MAP_IDX:
            return "Display coverage map (cloudiness index)";
        case MENU_OPTION::COVERAGE_MAP_LMH:
            return "Display coverage map (LMH symbols)";
        case MENU_OPTION::ATMOS_PRESSURE_IDX:
            return "Display atmospheric pressure (pressure index)";
        case MENU_OPTION::ATMOS_PRESSURE_LMH:
            return "Display atmospheric pressure (LMH symbols)";
        case MENU_OPTION::SUMMARY_REPORT:
            return "Summary Report";
        case MENU_OPTION::QUIT:
            return "Quit";
        default:
            return "";
    }
    return "";
}
