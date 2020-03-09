#ifndef math_hpp
#define math_hpp

#include "geom.hpp"

class Triangle;

namespace Math
{
    Point rotate_point(const Point& a_Pt, float a_Xrot, float a_Yrot, float a_Zrot);
    float line_sphere_discriminant(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SphereCenter, float a_Radius);
    Point line_sphere_intersect_point(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SphereCenter, float a_Delta);
    float a_discriminant(const Point& a_PtA, const Point& a_PtB);
    float b_discriminant(const Point& a_PtA, const Point& a_PtB, const Point& a_PtC);
    float c_discriminant(const Point& a_PtA, const Point& a_PtC, float a_Radius);
    float discriminant(float a, float b, float c);
    float *t_solutions(float a, float b, float a_Delta);
    float distance(const Point& a_PtA, const Point& a_PtB);
    Point closet_point(const Point& a_PtOri, const Point& a_PtA, const Point& a_PtB);
    bool is_closer(const Point& a_PtOri, const Point& a_PtA, const Point& a_PtB);
    Point line_sphere_solution(const Point& a_PtA, const Point& a_PtB, float t);
    Vector sphere_point_norm(const Point& a_PtA, const Point& a_SphereCenter);
    float triangle_area(float a_EdgeA, float a_EdgeB, float a_EdgeC);
    Point line_plane_intersect(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SurfacePos, const Vector& a_SurfaceNorm);
    Vector reflection(const Vector& a_VecIncidence, const Vector& a_Norm);
};

#endif /* math_hpp */
