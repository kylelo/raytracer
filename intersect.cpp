#include "math.hpp"
#include "object.hpp"
#include "camera.hpp"
#include "intersect.hpp"

#include <iostream>
#include <math.h>


bool Intersect::isLineSphereIntersect(const float &a_Delta)
{
    return a_Delta < 0 ? false : true;
}

bool Intersect::isLineTriangleIntersect(const Point &a_StartPt, const Vector &a_Vec, const Triangle &a_Tri)
{
    Vector t_Norm        = a_Tri.getNorm();
    Point  t_TriPtB      = a_Tri.getPointB();
    Point  t_IntersectPt = Math::line_plane_intersect(a_StartPt, a_Vec, t_TriPtB, t_Norm);

    return a_Tri.isPointInTriangle(t_IntersectPt);
}

//find whether the ray intersect with spheres
void Intersect::processSpheres()
{
    for (auto s : m_Object.m_Spheres)
    {
        Point t_SphereCenter = s.getCenter();
        float t_Radius       = s.getRadius();
        float t_Delta        = Math::line_sphere_discriminant(m_StartPos, m_VecFromStartPos, t_SphereCenter, t_Radius);
        bool  t_IsIntersect  = Intersect::isLineSphereIntersect(t_Delta);

        if (!t_IsIntersect)
        {
            continue;
        }

        Point t_IntersectPt = Math::line_sphere_intersect_point(m_StartPos, m_VecFromStartPos, t_SphereCenter, t_Delta);

        //choose the point closer to the camera
        if (Math::is_closer(m_StartPos, t_IntersectPt, m_IntersectPos))
        {
            m_IntersectPos = t_IntersectPt;
            m_SurfaceNorm  = Math::sphere_point_norm(m_IntersectPos, t_SphereCenter);
            m_ColorPos     = s.getColor();
        }
    }
}

//find whether the ray intersect with the tetrahedron
void Intersect::processTetrahedron()
{
    for (auto th : m_Object.m_Tetrahedrons)
    {
        for(auto tri : th.getTriangles())
        {
            if (Intersect::isLineTriangleIntersect(m_StartPos, m_VecFromStartPos, tri))
            {
                Point  t_Face        = tri.getPointB();
                Vector t_Norm        = tri.getNorm();
                Point  t_IntersectPt = Math::line_plane_intersect(m_StartPos, m_VecFromStartPos, t_Face, t_Norm);

                if (Math::is_closer(m_StartPos, t_IntersectPt, m_IntersectPos))
                {
                    m_IntersectPos = t_IntersectPt;
                    m_SurfaceNorm  = t_Norm;
                    m_ColorPos     = th.getColor();
                }
            }
        }
    }

}

//find whether the ray intersect with the plane
void Intersect::processPlane()
{
    for (auto p : m_Object.m_Planes)
    {
        Point  t_Face        = p.getCenter();
        Vector t_Norm        = p.getNorm();
        Point  t_IntersectPt = Math::line_plane_intersect(m_StartPos, m_VecFromStartPos, t_Face, t_Norm);

        if (Math::is_closer(m_StartPos, t_IntersectPt, m_IntersectPos))
        {
            //prevent the situation that m_StartPos hit its belonging face.
            if (Math::distance(t_IntersectPt, m_StartPos) > 2)
            {
                m_IntersectPos = t_IntersectPt;
                m_SurfaceNorm = t_Norm;
                m_IsGlazeSurface = true; //mark
            }
        }
    }
}
