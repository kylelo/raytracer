#include "math.hpp"

#include <iostream>
#include <math.h>

Point Math::rotate_point(const Point& a_PtA, float a_Xrot, float a_Yrot, float a_Zrot)
{
  //use (0,0,0) as center to rotate
    float xr = (a_Xrot / 180) * M_PI;
    float yr = (a_Yrot / 180) * M_PI;
    float zr = (a_Zrot / 180) * M_PI;
    float t_OriCoord[3] = {a_PtA.getX(), a_PtA.getY(), a_PtA.getZ()};
    float t_NewCoord[3] = {0,0,0}; //store new coordinate for rotated point

    //3D rotation matrix
    float t_RotMatrix[3][3] =
    {
        {cos(yr)*cos(zr), cos(xr)*sin(zr) + sin(xr)*sin(yr)*cos(zr),
         sin(xr)*sin(zr) - cos(xr)*sin(yr)*cos(zr)},
        {-cos(yr)*sin(zr), cos(xr)*cos(zr) - sin(xr)*sin(yr)*sin(zr),
          sin(xr)*cos(zr) + cos(xr)*sin(yr)*sin(zr)},
        {sin(yr), -sin(xr)*cos(yr), cos(xr)*cos(yr)}
    };

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            t_NewCoord[i] += t_RotMatrix[i][j] * t_OriCoord[j];
        }
    }

    return Point(t_NewCoord[0], t_NewCoord[1], t_NewCoord[2]);
}

float Math::line_sphere_discriminant(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SphereCenter, float a_Radius)
{
    Point t_PtA = a_StartPt;          //point A on the line
    Point t_PtB = a_StartPt + a_Vec;  //point B on the line
    Point t_PtC = a_SphereCenter;     //center of the sphere

    float a = Math::a_discriminant(t_PtA, t_PtB);
    float b = Math::b_discriminant(t_PtA, t_PtB, t_PtC);
    float c = Math::c_discriminant(t_PtA, t_PtC, a_Radius);

    return Math::discriminant(a, b, c); //function to determine whether intersect
}

//if there are two sols this function only return one closer to point a_StartPt
Point Math::line_sphere_intersect_point(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SphereCenter, float a_Delta)
{
    Point t_PtA = a_StartPt;          //point A on the line
    Point t_PtB = a_StartPt + a_Vec;  //point B on the line
    Point t_PtC = a_SphereCenter;     //center of the sphere

    float a = Math::a_discriminant(t_PtA, t_PtB);
    float b = Math::b_discriminant(t_PtA, t_PtB, t_PtC);
    float* t = Math::t_solutions(a, b, a_Delta);

    Point sol_1 = Math::line_sphere_solution(t_PtA, t_PtB, t[0]);
    Point sol_2 = Math::line_sphere_solution(t_PtA, t_PtB, t[1]);

    return Math::closet_point(t_PtA, sol_1, sol_2);
}

float Math::a_discriminant(const Point& a_PtA, const Point& a_PtB)
{
    return pow((a_PtB.getX() - a_PtA.getX()), 2.0)
         + pow((a_PtB.getY() - a_PtA.getY()), 2.0)
         + pow((a_PtB.getZ() - a_PtA.getZ()), 2.0);
}

float Math::b_discriminant(const Point& a_PtA, const Point& a_PtB, const Point& a_PtC)
{
    return ((a_PtB.getX() - a_PtA.getX()) * (a_PtA.getX() - a_PtC.getX())
         +  (a_PtB.getY() - a_PtA.getY()) * (a_PtA.getY() - a_PtC.getY())
         +  (a_PtB.getZ() - a_PtA.getZ()) * (a_PtA.getZ() - a_PtC.getZ())) * 2.0;
}

float Math::c_discriminant(const Point& a_PtA, const Point& a_PtC, float a_Radius)
{
    return pow((a_PtA.getX() - a_PtC.getX()), 2.0)
         + pow((a_PtA.getY() - a_PtC.getY()), 2.0)
         + pow((a_PtA.getZ() - a_PtC.getZ()), 2.0) - pow(a_Radius, 2.0);
}

float Math::discriminant(float a, float b, float c)
{
    return pow(b, 2.0) - 4.0 * a * c;
}

float* Math::t_solutions(float a, float b, float a_Delta)
{
    float* sols = new float[2];
    sols[0] = (-b + pow(a_Delta, 0.5)) / (2 * a);
    sols[1] = (-b - pow(a_Delta, 0.5)) / (2 * a);

    return sols;
}

//distance between two points
float Math::distance(const Point& a_PtA, const Point& a_PtB)
{
    return pow(pow(a_PtA.getX() - a_PtB.getX(), 2.0) +
               pow(a_PtA.getY() - a_PtB.getY(), 2.0) +
               pow(a_PtA.getZ() - a_PtB.getZ(), 2.0), 0.5);
}

//determine whether A or B point is closer to point ori
Point Math::closet_point(const Point& a_PtOri, const Point& a_PtA, const Point& a_PtB)
{
    float dist_A = Math::distance(a_PtOri, a_PtA);
    float dist_B = Math::distance(a_PtOri, a_PtB);
    return dist_A < dist_B ? a_PtA : a_PtB;
}

//determine whether A is closer to ori than B point
bool Math::is_closer(const Point& a_PtOri, const Point& a_PtA, const Point& a_PtB)
{
    float dist_A = Math::distance(a_PtOri, a_PtA);
    float dist_B = Math::distance(a_PtOri, a_PtB);
    return dist_A < dist_B ? true : false;
}

//solution for line sphere intersection
Point Math::line_sphere_solution(const Point& a_PtA, const Point& a_PtB, float t)
{
    float sol_x = a_PtA.getX() + (a_PtB.getX() - a_PtA.getX()) * t;
    float sol_y = a_PtA.getY() + (a_PtB.getY() - a_PtA.getY()) * t;
    float sol_z = a_PtA.getZ() + (a_PtB.getZ() - a_PtA.getZ()) * t;
    return Point(sol_x, sol_y, sol_z);
}

//calculate the a_Norm for the point on the surface
Vector Math::sphere_point_norm(const Point& a_PtA, const Point& p_sphere)
{
    return Vector(a_PtA.getX() - p_sphere.getX(),
                  a_PtA.getY() - p_sphere.getY(),
                  a_PtA.getZ() - p_sphere.getZ());
}

//Heron formula
float Math::triangle_area(float a_EdgeA, float a_EdgeB, float a_EdgeC)
{
    float s = (a_EdgeA + a_EdgeB + a_EdgeC) / 2.0;
    return pow( s * (s-a_EdgeA) * (s-a_EdgeB) * (s-a_EdgeC), 0.5);
}

//return value that can determine whether line plane instersect and the point
Point Math::line_plane_intersect(const Point& a_StartPt, const Vector& a_Vec, const Point& a_SurfacePos, const Vector& a_SurfaceNorm)
{
    float tri_D = -(a_SurfaceNorm.getX() * a_SurfacePos.getX()
                +   a_SurfaceNorm.getY() * a_SurfacePos.getY()
                +   a_SurfaceNorm.getZ() * a_SurfacePos.getZ());
    float temp_U = a_SurfaceNorm.getX() * a_StartPt.getX()
                 + a_SurfaceNorm.getY() * a_StartPt.getY()
                 + a_SurfaceNorm.getZ() * a_StartPt.getZ() + tri_D;
    float t_Delta = a_SurfaceNorm.dotProduct(a_Vec);

    if (t_Delta == 0) //line parallel the triangle face
    {
        return Point(10000, 10000, 10000);
    }

    float t = - temp_U / t_Delta; //for calculating intersection point
    float x_intersect = a_Vec.getX() * t + a_StartPt.getX();
    float y_intersect = a_Vec.getY() * t + a_StartPt.getY();
    float z_intersect = a_Vec.getZ() * t + a_StartPt.getZ();
    return Point(x_intersect, y_intersect, z_intersect);
}

Vector Math::reflection(const Vector& a_VecIncidence, const Vector& a_Norm)
{
    return a_VecIncidence - a_Norm * (a_VecIncidence.dotProduct(a_Norm)) * 2;
}
