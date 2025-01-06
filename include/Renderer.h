#ifndef RENDERER_H
#define RENDERER_H

#include "Declarations.h"

namespace Renderer {
    void RenderGrid(
        int **const data,
        const Vec2D &bottomLeft,
        const Vec2D &topRight,
        const RENDER_MODE renderMode);    
};

#endif