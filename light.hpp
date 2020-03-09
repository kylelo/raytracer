#ifndef light_hpp
#define light_hpp

class LambertLight
{
public:
    LambertLight():
        m_VecX(0), m_VecY(0), m_VecZ(0){}
    LambertLight(float xd, float yd, float zd):
        m_VecX(xd), m_VecY(yd), m_VecZ(zd){}

    Vector getLambertianLight() const;
    Point  getPos(const Point& a_SurfacePos) const;
    float  getLambertReflectIntensity(const Vector& a_LightSurfaceNorm) const;

private:
    float m_VecX, m_VecY, m_VecZ; //light direction
};

class AmbientLight
{
public:
    AmbientLight(): m_Intensity(0){}
    AmbientLight(float am):
    m_Intensity(am){}

    float getAmbientIntensity() const { return m_Intensity; };
private:
    float m_Intensity;
};

class SpecularShading
{
public:
    SpecularShading():
        m_VecX(0), m_VecY(0), m_VecZ(0), m_CoefN(0), m_CoefSpeculer(0){}
    SpecularShading(float xd, float yd, float zd, float n, float ks):
        m_VecX(xd), m_VecY(yd), m_VecZ(zd), m_CoefN(n), m_CoefSpeculer(ks){}

    float  getSpecularIntensity(Vector m_CamRay, Vector m_SurfaceNorm) const;
    Point  getPos(const Point& a_SurfacePos) const;
    Vector getSpecularVec() const { return Vector(m_VecX, m_VecY, m_VecZ); }
private:
    float m_VecX, m_VecY, m_VecZ;
    float m_CoefN, m_CoefSpeculer;
};

struct Light
{
    AmbientLight m_Ambient;
    std::vector<LambertLight> m_Lamberts;
    std::vector<SpecularShading> m_Speculars;
};

class Lighting
{
public:
    Lighting(Object obj):
        m_Object(obj), m_RecordBlockPoint(Point(1000,1000,1000)) {}

    float lightAccumulation(const Intersect& a_Intersect, const Vector& a_CamRay, const Light& a_Light);
    bool  isBlock(Point a_SurfacePos, Point a_LightPos);

private:
    Object m_Object;
    Point  m_RecordBlockPoint;
    Point  updateSphereBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos);
    Point  updateTetrahedronsBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos);
    Point  updatePlaneBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos);
};





#endif /* light_hpp */
