#include "WeatherApp.h"
#include "Input.h"
#include "Utils.h"

#include <iostream>

void WeatherApp::PrintMainMenu() {
    std::cout << ANSI::BLUE << std::endl;
    std::cout << "Student ID:   9085610" << std::endl;
    std::cout << "Student Name: Alexander Neo" << std::endl;
    std::cout << "-------------------------" << std::endl;
    std::cout << ANSI::DEFAULT;
    std::cout << "Welcome to Weather Information Processing System!";
    Utils::PrintNewlines(2);
};

void WeatherApp::HandleOption(const MENU_OPTION menuOption) {
    switch (menuOption) {
        case MENU_OPTION::PROCESS_CONFIG_FILE: {
            
            break;
        }
        case MENU_OPTION::DISPLAY_CITY_MAP: {
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
