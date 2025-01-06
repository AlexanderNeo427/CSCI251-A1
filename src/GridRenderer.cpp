#include "GridRenderer.h"
#include <iostream>

void GridRenderer::RenderGrid(
    int **const data,
    const Vec2D &bottomLeft,
    const Vec2D &topRight,
    const RENDER_MODE renderMode) {

    // const int rangeX = (topRight.x - bottomLeft.x) + 1;
    // const int rangeY = (topRight.y - bottomLeft.y) + 1;
    // const int x_charWidth = std::max(
    //     std::to_string(topRight.x).length(), 
    //     std::to_string(bottomLeft.x).length()
    // );
    // const int y_charWidth = std::max(
    //     std::to_string(topRight.y).length(), 
    //     std::to_string(bottomLeft.y).length()
    // );
    // for (int y = rangeY - 1; y >= 0; y--) {
    //     for (int x = 0; x < rangeX; x++) {
    //         // std::cout << data[x][y] << " ";
    //         // switch (renderMode) {
    //         //     std::cout << "#" << std::endl;
    //         //     // default: break;
    //         // }
    //     }
    //     std::cout << std::endl;
    // }
}