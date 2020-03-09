#include "geom.hpp"
#include "math.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "intersect.hpp"
#include "light.hpp"
#include "scene.hpp"
#include "renderer.hpp"

Color Renderer::render_color_for_pixel(Scene& a_Scene, int a_iPixelCoord, int a_jPixelCoord)
{

    Point t_CamPos = a_Scene.getCamera().getCamPixelCoordinate(a_iPixelCoord, a_jPixelCoord);
    //Switch parrallel camera or perspective camera here.
    Vector t_VecCam = a_Scene.getCamera().getParallelCamRay();
    //Vector t_VecCam = a_Scene.camera.getPerspectiveCamRay(a_iPixelCoord, a_jPixelCoord, window_Height, window_Width);

    Intersect t_Intersect(t_CamPos, t_VecCam, a_Scene.getObject());
    Point t_IntersetPos = t_Intersect.getPos();

    Vector t_Norm = t_Intersect.getNorm();
    Color t_Color = t_Intersect.getColor();

    float t_TotalLightIntensity = 0;

    Lighting t_Lighting = Lighting(a_Scene.getObject());

    //processing the reflection of the glaze object
    if (t_Intersect.isGlaze() == true)
    {
        t_Norm.normalize();
        Vector t_VecReflect = Math::reflection(t_VecCam, t_Norm);

        Intersect t_IntersectGlaze(t_IntersetPos, t_VecReflect, a_Scene.getObject());

        t_TotalLightIntensity = t_Lighting.lightAccumulation(t_IntersectGlaze, t_VecCam, a_Scene.getLight());

        t_Color = Color(150, 150, 150)*0.8 + t_IntersectGlaze.getColor()*0.2;
    }
    else
    {
        t_TotalLightIntensity = t_Lighting.lightAccumulation(t_Intersect, t_VecCam, a_Scene.getLight());
    }

    if (t_TotalLightIntensity > 0)
    {
        Color color_processed = t_Color * t_TotalLightIntensity;
        int r = color_processed.getRed();
        int g = color_processed.getGreen();
        int b = color_processed.getBlue();

        return Color(r < 255 ? r : 255, g < 255 ? g : 255, b < 255 ? b : 255);
    }
    else
        return Color(0,0,0);
}
