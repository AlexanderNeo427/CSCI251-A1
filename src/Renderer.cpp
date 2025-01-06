#include "Renderer.h"
#include <iomanip>
#include <iostream>

void Renderer::RenderGrid(
    int **const data, const Vec2D &bottomLeft,
    const Vec2D &topRight, const RENDER_MODE renderMode) {

    const int rangeX = (topRight.x - bottomLeft.x) + 1;
    const int rangeY = (topRight.y - bottomLeft.y) + 1;

    const int xCharWidth = std::max(
        std::to_string(topRight.x).length(),
        std::to_string(bottomLeft.x).length()
    ) + 1;
    const int yCharWidth = std::max(
        std::to_string(topRight.y).length(),
        std::to_string(bottomLeft.y).length()
    ) + 1;
    
    const int leftPad = 0;
    const int wallLength = rangeX + 2;

    // Roof
    std::cout << std::setw(leftPad + yCharWidth) << ""; // Left-pad
    for (int i = 0; i < wallLength; i++) {
        std::cout << ANSI::YELLOW << std::setw(xCharWidth) << "#";
    }
    std::cout << ANSI::DEFAULT << std::endl;

    // Middle
    for (int y = rangeY - 1; y >= 0; y--) {
        std::cout << std::setw(leftPad) << ""; // Left-pad
        std::cout << std::setw(yCharWidth) << std::right << (y + bottomLeft.y);
        std::cout << ANSI::YELLOW << std::setw(xCharWidth) << "#" << ANSI::DEFAULT;
        for (int x = 0; x < rangeX; x++) {
            std::cout << std::setw(xCharWidth) << data[x][y];
        }
        std::cout << ANSI::YELLOW << std::setw(xCharWidth) << "#" << ANSI::DEFAULT << std::endl;
    }

    // Floor
    std::cout << std::setw(leftPad + yCharWidth) << ""; // Left-pad
    for (int i = 0; i < wallLength; i++) {
        std::cout << ANSI::YELLOW << std::setw(xCharWidth) << "#";
    }
    std::cout << ANSI::DEFAULT << std::endl;

    // X-axis coords
    std::cout << std::setw(leftPad + yCharWidth + xCharWidth) << "";
    for (int x = 0; x < rangeX; x++) {
        std::cout << std::setw(xCharWidth) << (x + bottomLeft.x);
    }
    std::cout << std::endl;
}