#include "WeatherApp.h"
#include "DataLoader.h"
#include "Input.h"
#include "Renderer.h"
#include "SummaryReport.h"
#include "Utils.h"
#include <iostream>

void WeatherApp::PrintMainMenu() {
    std::cout << ANSI::CYAN << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "| Student ID:   9085610       |" << std::endl;
    std::cout << "| Student Name: Alexander Neo |" << std::endl;
    std::cout << "-------------------------------" << std::endl;
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
            const StrInputStatus inputStatus = Input::AwaitStrInput("Please enter filename: ");
            if (!inputStatus.success) {
                std::cout << "Error was trying to read input: " << inputStatus.message << std::endl;
                Input::AwaitEnterInput();
                break;
            }

            std::string failReason = "";
            const bool parseSuccess = DataLoader::ParseFile(inputStatus.input, gridData, failReason);
            if (!parseSuccess) {
                std::cerr << failReason << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Utils::PrintNewlines(1);
            std::cout << "All records successfully stored. Going back to main menu..." << std::endl;
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::DISPLAY_CITY_MAP: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Renderer::RenderGrid(
                gridData.cityGrid, gridData.cityNames,
                gridData.bottomLeft, gridData.topRight, RENDER_MODE::CITY);
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::CLOUD_MAP_IDX: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Renderer::RenderGrid(
                gridData.cloudGrid, gridData.cityNames,
                gridData.bottomLeft, gridData.topRight, RENDER_MODE::INDEX);
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::CLOUD_MAP_LMH: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Renderer::RenderGrid(
                gridData.cloudGrid, gridData.cityNames,
                gridData.bottomLeft, gridData.topRight, RENDER_MODE::LMH);
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::ATMOS_PRESSURE_IDX: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Renderer::RenderGrid(
                gridData.pressureGrid, gridData.cityNames,
                gridData.bottomLeft, gridData.topRight, RENDER_MODE::INDEX);
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::ATMOS_PRESSURE_LMH: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            Renderer::RenderGrid(
                gridData.pressureGrid, gridData.cityNames,
                gridData.bottomLeft, gridData.topRight, RENDER_MODE::LMH);
            Input::AwaitEnterInput();
            break;
        }
        case MENU_OPTION::SUMMARY_REPORT: {
            if (!gridData.isDataLoaded) {
                std::cout << "No config data loaded..." << std::endl;
                Input::AwaitEnterInput();
                break;
            }
            SummaryReport::GenerateSummaryReport(gridData);
            Input::AwaitEnterInput();
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
        case MENU_OPTION::CLOUD_MAP_IDX:
            return "Display coverage map (cloudiness index)";
        case MENU_OPTION::CLOUD_MAP_LMH:
            return "Display coverage map (LMH symbols)";
        case MENU_OPTION::ATMOS_PRESSURE_IDX:
            return "Display atmospheric pressure (pressure index)";
        case MENU_OPTION::ATMOS_PRESSURE_LMH:
            return "Display atmospheric pressure (LMH symbols)";
        case MENU_OPTION::SUMMARY_REPORT:
            return "Summary Report";
        case MENU_OPTION::QUIT:
            return "Quit";
        default: {
            const std::string msg = "WeatherApp::OptionToText(), menu option is not implemented: ";
            const int optionIndex = static_cast<int>(menuOption);
            return msg + std::to_string(optionIndex);
        }
    }
    return "";
}
