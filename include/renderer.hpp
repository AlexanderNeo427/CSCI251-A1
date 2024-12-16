#ifndef RENDERER_H
#define RENDERER_H

#include "declarations.hpp"
#include <cmath>
#include <iostream>

namespace Renderer {
    void RenderGrid(const GridData &gridData, const RENDER_MODE renderMode) {
        const int contentWidth = (gridData.rangeX.max - gridData.rangeX.min) + 1;
        const int contentHeight = (gridData.rangeY.max - gridData.rangeY.min) + 1;

        // Top border
        std::cout << "  ";
        for (int i = 0; i < (contentWidth + 2); i++) {
            std::cout << "# ";
        }
        std::cout << std::endl;

        // Content + middle borders
        for (int y = contentHeight - 1; y >= 0; y--) {
            std::cout << y << " # ";
            if (renderMode == RENDER_MODE::CITY) {
                for (int x = 0; x < contentWidth; x++) {
                    if (gridData.arr[x][y] == 0) {
                        std::cout << "  ";
                    } else {
                        std::cout << gridData.arr[x][y] << " ";
                    }
                }
            } else if (renderMode == RENDER_MODE::INDEX) {
                for (int x = 0; x < contentWidth; x++) {
                    const double value = static_cast<double>(gridData.arr[x][y]);
                    std::cout << floor(value / 10.) << " ";
                }
            } else if (renderMode == RENDER_MODE::LMH) {
                for (int x = 0; x < contentWidth; x++) {
                    const int value = gridData.arr[x][y];
                    if (value >= 0 && value < 35) {
                        std::cout << "L ";
                    } else if (value >= 35 && value < 65) {
                        std::cout << "M ";
                    } else {
                        std::cout << "H ";
                    }
                }
            }
            std::cout << "#" << std::endl;
        }

        // Bottom border
        std::cout << "  ";
        for (int i = 0; i < (contentWidth + 2); i++) {
            std::cout << "# ";
        }
        std::cout << std::endl;

        std::cout << "    ";
        for (int i = 0; i < contentWidth; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
} // namespace Renderer

#endif