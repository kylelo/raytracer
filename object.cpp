#include "math.hpp"
#include "object.hpp"


#include <iostream>
#include <math.h>

using namespace std;


Vector Triangle::getNorm() const
{
    Vector t_VecA(m_PtA.getX() - m_PtB.getX(), m_PtA.getY() - m_PtB.getY(),
                                               m_PtA.getZ() - m_PtB.getZ());
    Vector t_VecB(m_PtC.getX() - m_PtB.getX(), m_PtC.getY() - m_PtB.getY(),
                                               m_PtC.getZ() - m_PtB.getZ());
    return t_VecA.crossProduct(t_VecB);
}

Vector Triangle::getVecA() const
{
    return Vector(m_PtA.getX() - m_PtB.getX(),
                  m_PtA.getY() - m_PtB.getY(),
                  m_PtA.getZ() - m_PtB.getZ());
}

Vector Triangle::getVecB() const
{
    return Vector(m_PtC.getX() - m_PtB.getX(),
                  m_PtC.getY() - m_PtB.getY(),
                  m_PtC.getZ() - m_PtB.getZ());
}

bool Triangle::isPointInTriangle(Point a_Point) const
{
    //measure the length of each edge
    float t_DistAB = Math::distance(m_PtA, m_PtB);
    float t_DistBC = Math::distance(m_PtB, m_PtC);
    float t_DistCA = Math::distance(m_PtC, m_PtA);
    //the distance between interset point to each vetex
    float dist_cA = Math::distance(a_Point, m_PtA);
    float dist_cB = Math::distance(a_Point, m_PtB);
    float dist_cC = Math::distance(a_Point, m_PtC);

    //if the sum of three sub triangle equals to large one, point is inside tri
    float area_all = Math::triangle_area(t_DistAB, t_DistBC, t_DistCA);
    float area_A   = Math::triangle_area(dist_cA, dist_cB, t_DistAB);
    float area_B   = Math::triangle_area(dist_cB, dist_cC, t_DistBC);
    float area_C   = Math::triangle_area(dist_cC, dist_cA, t_DistCA);

    if (abs(area_A + area_B + area_C - area_all) < 1)
        return true;
    else
        return false;
}



Tetrahedron::Tetrahedron(Point p_c, float edge_length, Color c)
    : m_TetrahedronCenter(p_c), m_Color(c)
{
    float x = m_TetrahedronCenter.getX();
    float y = m_TetrahedronCenter.getY();
    float z = m_TetrahedronCenter.getZ();

    //shortest edge of 30 60 90 triangle
    float se =  edge_length * pow(3.0,0.5) / 6.0;
    m_PtA = Point(         x,                     y, z + 2 * se);
    m_PtB = Point(    x + se, y + edge_length * 0.5,     z - se);
    m_PtC = Point(    x + se, y - edge_length * 0.5,     z - se);
    m_PtD = Point(x - 2 * se,                     y,     z - se);

    tri.push_back( Triangle(m_PtA, m_PtB, m_PtC) );
    tri.push_back( Triangle(m_PtA, m_PtD, m_PtB) );
    tri.push_back( Triangle(m_PtA, m_PtC, m_PtD) );
    tri.push_back( Triangle(m_PtB, m_PtD, m_PtC) );
}


Vector Plane::getNorm() const
{
    Vector t_VecA = Point::getVec(m_PlaneCenter, m_PtA);
    Vector t_VecB = Point::getVec(m_PlaneCenter, m_PtB);
    return t_VecA.crossProduct(t_VecB);
}
