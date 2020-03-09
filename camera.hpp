#ifndef camera_hpp
#define camera_hpp

class Camera
{
public:
    Camera ():
        m_CamPos(Point(0,0,0)), m_PixelInterval(0), m_Xrot(0), m_Yrot(0), m_Zrot(0){}
    Camera (const Point& cp, float pi, float xr, float yr, float zr):
        m_CamPos(cp), m_PixelInterval(pi), m_Xrot(xr), m_Yrot(yr), m_Zrot(zr){}

    //get the realworld coordinate of pixel on camera
    Point  getCamPixelCoordinate(int a_iPixelCoord, int a_jPixelCoord) const;
    Vector getParallelCamRay() const;
    Vector getPerspectiveCamRay(int a_iPixelCoord, int a_jPixelCoord, int a_Height, int a_Width) const;
    void   setPos(const Point& a_CamPos, float a_PixelInterval, float a_Xrot, float a_Yrot, float a_Zrot);

private:
    Point m_CamPos;              //camera coordinate (position for cam[0][0])
    float m_Xrot, m_Yrot, m_Zrot;  //camera rotation
    float m_PixelInterval;       //distance between two connected pixel in world
};

#endif
