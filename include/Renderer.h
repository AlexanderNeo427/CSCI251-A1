#ifndef RENDERER_H
#define RENDERER_H

#include "Declarations.h"

namespace Renderer {
    void RenderGrid(
        int **const data, 
        const std::array<std::string, CITY_ID_COUNT>& cityNames,
        const Vec2D &bottomLeft,
        const Vec2D &topRight,
        const RENDER_MODE renderMode);    
};

#endif