#ifndef GRID_RENDERER_H
#define GRID_RENDERER_H

#include "Declarations.h"

namespace GridRenderer {
    void RenderGrid(
        int **const data,
        const Vec2D &bottomLeft,
        const Vec2D &topRight,
        const RENDER_MODE renderMode);
};

#endif