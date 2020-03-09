#ifndef intersect_hpp
#define intersect_hpp

class Intersect{
public:
    Intersect(Point ps, Vector vd, Object obj):
        m_StartPos(ps), m_VecFromStartPos(vd), m_Object(obj),
        m_IntersectPos(Point(1000, 1000, 1000)),
        m_SurfaceNorm(Vector(0,0,0)), m_ColorPos(Color(0,0,0)),
        m_IsGlazeSurface(false)
    {
        processSpheres();
        processTetrahedron();
        processPlane();
    }

    Point  getPos()   const { return m_IntersectPos;   }
    Vector getNorm()  const { return m_SurfaceNorm;    }
    Color  getColor() const { return m_ColorPos;       }
    bool   isGlaze()  const { return m_IsGlazeSurface; }

    bool isLineSphereIntersect(const float &a_Delta);
    bool isLineTriangleIntersect(const Point &a_StartPt, const Vector &a_Vec, const Triangle &a_Tri);

private:
    Point  m_StartPos;
    Vector m_VecFromStartPos;
    Object m_Object;
    Point  m_IntersectPos;
    Vector m_SurfaceNorm;
    Color  m_ColorPos;
    bool   m_IsGlazeSurface;

    void processSpheres();
    void processTetrahedron();
    void processPlane();
    // Add other objects here...

};

#endif /* intersect_hpp */
