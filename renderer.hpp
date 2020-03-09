#ifndef renderer_hpp
#define renderer_hpp

#include <iostream>
#include <vector>

namespace Renderer
{
    Color render_color_for_pixel(Scene& a_Scene, int a_iPixelCoord, int a_jPixelCoord);
};

#endif /* renderer_hpp */
