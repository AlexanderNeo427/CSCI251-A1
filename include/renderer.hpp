#ifndef RENDERER_H
#define RENDERER_H

#include "declarations.hpp"
#include <iostream>

namespace Renderer {
    void RenderGrid(const GridData &gridData) {
        const int contentWidth = (gridData.rangeX.max - gridData.rangeX.min) + 1;
        const int contentHeight = (gridData.rangeY.max - gridData.rangeY.min) + 1;

        // Top border
        std::cout << "    ";
        for (int i = 0; i < contentWidth; i++) {
            std::cout << "# ";
        }
        std::cout << std::endl;

        // Content + middle borders
        for (int y = contentHeight - 1; y >= 0; y--) {
            std::cout << y + 1 << " # ";
            for (int x = 0; x < contentWidth; x++) {
                if (gridData.arr[x][y] == 0) {
                    std::cout << "  ";
                } else {
                    std::cout << gridData.arr[x][y] << " ";
                }
            }
            std::cout << "#" << std::endl;
        }

        // Bottom border
        std::cout << "    ";
        for (int i = 0; i < contentWidth; i++) {
            std::cout << "# ";
        }
        std::cout << std::endl;
    }
} // namespace Renderer

#endif