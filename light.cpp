#include "geom.hpp"
#include "object.hpp"

#include "math.hpp"
#include "intersect.hpp"
#include "light.hpp"
#include <iostream>
#include <math.h>

using namespace std;

Vector LambertLight::getLambertianLight() const
{
    return Vector(m_VecX, m_VecY, m_VecZ);
}

Point LambertLight::getPos(const Point& a_SurfacePos) const
{
    return a_SurfacePos - LambertLight::getLambertianLight() * 1000;
}

float LambertLight::getLambertReflectIntensity(const Vector& a_LightSurfaceNorm) const
{
    Vector t_VecLambert = LambertLight::getLambertianLight() * (-1);
    auto t_LightSurfaceNorm = a_LightSurfaceNorm;

    t_VecLambert.normalize();
    t_LightSurfaceNorm.normalize();

    float t_Dot = t_VecLambert.dotProduct(t_LightSurfaceNorm);

    return t_Dot > 0 ? t_Dot : 0;
}

float SpecularShading::getSpecularIntensity(Vector a_CamRay, Vector a_SurfaceNorm) const
{
    Vector t_VecLight = SpecularShading::getSpecularVec();

    a_CamRay.normalize();
    t_VecLight.normalize();
    a_SurfaceNorm.normalize();

    Vector t_VecReflect = Math::reflection(t_VecLight, a_SurfaceNorm);
    float  t_Dot        = t_VecReflect.dotProduct(a_CamRay * (-1));

    t_Dot = t_Dot > 0 ? t_Dot : 0;

    return m_CoefSpeculer * pow(t_Dot, m_CoefN);
}

Point SpecularShading::getPos(const Point& a_SurfacePos) const
{
    return a_SurfacePos - SpecularShading::getSpecularVec() * 1000;
}


//return the total birghtness of a point on surface
float Lighting::lightAccumulation(const Intersect& a_Intersect, const Vector& a_CamRay, const Light& a_Light)
{
    Point t_IntersectPos = a_Intersect.getPos();
    Vector t_Norm        = a_Intersect.getNorm();

    bool t_IsLambertBlock  = isBlock(t_IntersectPos, a_Light.m_Lamberts[0].getPos(t_IntersectPos));
    bool t_IsSpecularBlock = isBlock(t_IntersectPos, a_Light.m_Speculars[0].getPos(t_IntersectPos));

    return   (!t_IsLambertBlock)
           * a_Light.m_Lamberts[0].getLambertReflectIntensity(t_Norm)
           + (!t_IsSpecularBlock)
           * a_Light.m_Speculars[0].getSpecularIntensity(a_CamRay, t_Norm)
           + a_Light.m_Ambient.getAmbientIntensity();
}

bool Lighting::isBlock(Point a_SurfacePos, Point a_LightPos)
{
    //if the closet point is the suface point, it means there is no block
    Vector m_LightSurfaceVec = Point::getVec(a_SurfacePos, a_LightPos);
    m_RecordBlockPoint = Point(1000, 1000, 1000);

    updateSphereBlockPoint(m_LightSurfaceVec, a_LightPos);
    updateTetrahedronsBlockPoint(m_LightSurfaceVec, a_LightPos);
    updatePlaneBlockPoint(m_LightSurfaceVec, a_LightPos);

    return Math::distance(m_RecordBlockPoint, a_SurfacePos) < 0.5 ? false : true;
}


Point Lighting::updateSphereBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos)
{
    for (auto s : m_Object.m_Spheres)
    {
        Point t_SphereCenter = s.getCenter();
        float t_Radius       = s.getRadius();
        float t_Delta        = Math::line_sphere_discriminant(a_LightPos, a_LightSurfaceVec, t_SphereCenter, t_Radius);
        Point t_IntersectPos = Math::line_sphere_intersect_point(a_LightPos, a_LightSurfaceVec, t_SphereCenter, t_Delta);
        m_RecordBlockPoint   = Math::closet_point(a_LightPos, t_IntersectPos, m_RecordBlockPoint);
    }
}

Point Lighting::updateTetrahedronsBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos)
{
    for (auto th : m_Object.m_Tetrahedrons)
    {
        for (auto tri : th.getTriangles())
        {
            Point        t_TriPt = tri.getPointB(); //get a point on triangle
            Vector        t_Norm = tri.getNorm();
            Point t_IntersectPos = Math::line_plane_intersect(a_LightPos, a_LightSurfaceVec, t_TriPt, t_Norm);

            if(!tri.isPointInTriangle(t_IntersectPos))
            {
                continue;
            }

            m_RecordBlockPoint = Math::closet_point(a_LightPos, t_IntersectPos, m_RecordBlockPoint);
        }
    }
}

Point Lighting::updatePlaneBlockPoint(const Vector& a_LightSurfaceVec, const Point& a_LightPos)
{
    for (auto p : m_Object.m_Planes)
    {
        Point     t_PlanePos = p.getCenter();
        Vector        t_Norm = p.getNorm();
        Point t_IntersectPos = Math::line_plane_intersect(a_LightPos, a_LightSurfaceVec, t_PlanePos, t_Norm);

        m_RecordBlockPoint = Math::closet_point(a_LightPos, t_IntersectPos, m_RecordBlockPoint);
    }
}
