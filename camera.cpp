#include "geom.hpp"

#include "math.hpp"
#include "camera.hpp"

Point Camera::getCamPixelCoordinate(int a_iPixelCoord, int a_jPixelCoord) const
{

    //we set left up (0,0) of camera pixel as original point (0,0,0)
    //then rotate the other pixels in the array
    Point t_Pt(m_PixelInterval * a_jPixelCoord, m_PixelInterval * a_iPixelCoord, 0);
    Point t_RotatedPt = Math::rotate_point(t_Pt, m_Xrot, m_Yrot, m_Zrot);

    //move back to the actual location
    return t_RotatedPt + m_CamPos;
}

Vector Camera::getParallelCamRay() const
{
    //The end point of parallel ray before rotation (start point is (0,0,0))
    Point end_pt(0, 0, -1);

    //rotate ray vector to be perpendicular to camera array(face)
    Point new_end_pt = Math::rotate_point(end_pt, m_Xrot, m_Yrot, m_Zrot);

    return Vector( new_end_pt.getX(),
                   new_end_pt.getY(),
                   new_end_pt.getZ() );
}

Vector Camera::getPerspectiveCamRay(int a_iPixelCoord, int a_jPixelCoord, int a_Height, int a_Width) const
{
    Point t_EyePos(a_Height / 2, a_Width / 2, (a_Height + a_Width) / 4);

    Point t_RotatedEyePos = Math::rotate_point(t_EyePos, m_Xrot, m_Yrot, m_Zrot);
    Point t_PixelPos      = getCamPixelCoordinate(a_iPixelCoord, a_jPixelCoord);

    return Point::getVec(t_RotatedEyePos, t_PixelPos);
}

void Camera::setPos(const Point& a_CamPos, float a_PixelInterval, float a_Xrot, float a_Yrot, float a_Zrot)
{
    m_CamPos        = a_CamPos;
    m_PixelInterval = a_PixelInterval;
    m_Xrot          = a_Xrot;
    m_Yrot          = a_Yrot;
    m_Zrot          = a_Zrot;
}
