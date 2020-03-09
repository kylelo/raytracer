#ifndef geom_hpp
#define geom_hpp

class Vector
{
public:
    Vector(float n):
        m_VecX(n), m_VecY(n), m_VecZ(n){}
    Vector(float x, float y, float z):
        m_VecX(x), m_VecY(y), m_VecZ(z){}

    float getX() const { return m_VecX; }
    float getY() const { return m_VecY; }
    float getZ() const { return m_VecZ; }

    //Math operator for vector
    Vector operator + (const float  & a_Num) const;    //Plus operator (number)
    Vector operator + (const Vector & a_Vec) const;    //Plus operator (vector)
    Vector operator - (const float  & a_Num) const;    //Minus (number)
    Vector operator - (const Vector & a_Vec) const;    //Minus (vector)
    Vector operator * (const float  & a_Num) const;    //Mutiplication (number)
    Vector operator / (const float  & a_Num) const;    //Divider (number)
    Vector operator / (const Vector & a_Vec) const;    //Divider (vector)

    Vector crossProduct(const Vector & a_Vec) const;   //Cross product
    Vector normalize();                                //Normalize the vector itself
    float  dotProduct(const Vector & a_Vec) const;     //Dot product
    float  magni() const;                              //Calculate the magnitude

private:
    float m_VecX, m_VecY, m_VecZ;
};

class Point
{
public:
    Point():
        m_PosX(0), m_PosY(0), m_PosZ(0){}
    Point(float x, float y, float z):
        m_PosX(x), m_PosY(y), m_PosZ(z){}

    float getX() const { return m_PosX; }
    float getY() const { return m_PosY; }
    float getZ() const { return m_PosZ; }

    //Math operatoer for point
    Point operator + (const Vector &a_Vec) const;   //translate a point
    Point operator + (const Point  &a_Pt ) const;   //translate a point
    Point operator - (const Vector &a_Vec) const;   //translate a point
    Point operator - (const Point  &a_Pt ) const;   //translate a point
    Point operator / (const float  &a_Num) const;
    Point operator * (const float  &a_Num) const;

    Vector static getVec(const Point &a_SrartPt, const Point &a_EndPt);

private:
    float m_PosX, m_PosY, m_PosZ;
};

class Color
{
public:
    Color(float r, float g, float b):
        m_Red(r), m_Green(g), m_Blue(b){}

    float getRed()   const { return m_Red;   }
    float getGreen() const { return m_Green; }
    float getBlue()  const { return m_Blue;  }

    Color operator * (const float &a_Brightness) const;
    Color operator + (const Color &a_Color)      const;

private:
    float m_Red, m_Green, m_Blue;
};

#endif /* geom_hpp */
