#ifndef object_hpp
#define object_hpp

#include <iostream>
#include <vector>

class Sphere
{
public:
    Sphere():
        m_SphereCenter(Point(0,0,0)), radius(0), m_Color(Color(0,0,0)){}
    Sphere(Point p, float r, Color c):
        m_SphereCenter(p), radius(r), m_Color(c){}

    float getX() const { return m_SphereCenter.getX(); }
    float getY() const { return m_SphereCenter.getY(); }
    float getZ() const { return m_SphereCenter.getZ(); }

    float getRadius() const { return radius; }
    Point getCenter() const { return m_SphereCenter; }
    Color getColor() const { return m_Color; }

    void setCenter(Point a_Point) const {}
    void setRadius(float a_Radius) const {}
    void setColor(Color a_Color) const {}

private:
    Point m_SphereCenter;
    float radius;
    Color m_Color;
};




class Triangle
{
public:
    Triangle():
        m_PtA(Point(0,0,0)), m_PtB(Point(0,0,0)), m_PtC(Point(0,0,0)){}
    Triangle(Point a, Point b, Point c):
        m_PtA(a), m_PtB(b), m_PtC(c){}
    Point getPointA() const { return m_PtA; }
    Point getPointB() const { return m_PtB; }
    Point getPointC() const { return m_PtC; }
    Vector getNorm() const;
    Vector getVecA() const;
    Vector getVecB() const;
    bool isPointInTriangle(Point a_Point) const;

private:
    Point m_PtA, m_PtB, m_PtC;
};


class Tetrahedron
{
public:
    Tetrahedron():
        m_TetrahedronCenter(Point(0, 0, 0)), m_Color(Color(0, 0, 0)){}
    Tetrahedron(Point m_TetrahedronCenter, float edge_lenth, Color m_Color);

    std::vector<Triangle> getTriangles() const { return tri;}
    Color getColor() const { return m_Color; }

private:
    Point     m_PtA, m_PtB, m_PtC, m_PtD;
    Point     m_TetrahedronCenter;
    std::vector<Triangle> tri;
    Color     m_Color;
};




class Plane
{
public:
    Plane():
        m_PlaneCenter(Point(0, 0, 0)), m_PtA(Point(0, 0, 0)), m_PtB(Point(0, 0, 0)){}
    Plane(Point pc, Point a, Point b):
        m_PlaneCenter(pc), m_PtA(a), m_PtB(b){}

    Point getCenter(){ return m_PlaneCenter; }
    Point getPointA(){ return m_PtA; }
    Point getPointB(){ return m_PtB; }

    Vector getNorm() const;

private:
    Point m_PlaneCenter;     //use to control position
    Point m_PtA, m_PtB;   //another two points on plane
};




struct Object
{
    std::vector<Sphere>      m_Spheres;
    std::vector<Tetrahedron> m_Tetrahedrons;
    std::vector<Plane>       m_Planes;
    // Add other objects here
};



#endif /* object_hpp */
