#include "geom.hpp"

#include <iostream>
#include <math.h>

using namespace std;

/********************Math operator for vector*********************/

//Plus operator (number)
Vector Vector::operator + (const float &a_Num) const
{
    return Vector(m_VecX + a_Num, m_VecY + a_Num, m_VecZ + a_Num);
}

//Plus operator (vector)
Vector Vector::operator + (const Vector &a_Vec) const
{
    return Vector(m_VecX + a_Vec.getX(), m_VecY + a_Vec.getY(), m_VecZ + a_Vec.getY());
}

//Minus (number)
Vector Vector::operator - (const float &a_Num) const
{
    return Vector(m_VecX - a_Num, m_VecY - a_Num, m_VecZ - a_Num);
}

//Minus (vector)
Vector Vector::operator - (const Vector &a_Vec) const
{
    return Vector(m_VecX - a_Vec.getX(), m_VecY - a_Vec.getY(), m_VecZ - a_Vec.getZ());
}

//Mutiplication (number)
Vector Vector::operator * (const float &a_Num) const
{
    return Vector(m_VecX * a_Num, m_VecY * a_Num, m_VecZ * a_Num);
}

//Divider (number)
Vector Vector::operator / (const float &a_Num) const
{
    return Vector(m_VecX / a_Num, m_VecY / a_Num, m_VecZ / a_Num);
}

//Divider (vector)
Vector Vector::operator / (const Vector &a_Vec) const
{
    return Vector(m_VecX / a_Vec.getX(), m_VecY / a_Vec.getY(), m_VecZ / a_Vec.getZ());
}

//dot product
float Vector::dotProduct(const Vector &a_Vec) const
{
    return m_VecX * a_Vec.getX() + m_VecY * a_Vec.getY() + m_VecZ * a_Vec.getZ();
}

//cross product
Vector Vector::crossProduct(const Vector &a_Vec) const
{
    float t_NormX = m_VecY * a_Vec.getZ() - m_VecZ * a_Vec.getY();
    float t_NormY = m_VecZ * a_Vec.getX() - m_VecX * a_Vec.getZ();
    float t_NormZ = m_VecX * a_Vec.getY() - m_VecY * a_Vec.getX();
    return Vector(t_NormX, t_NormY, t_NormZ);
}

//Magnitude
float Vector::magni() const
{
    return sqrt(pow(m_VecX, 2)+pow(m_VecY, 2)+pow(m_VecZ, 2));
}

//Normalization
Vector Vector::normalize()
{
    float t_Inver = 1 / Vector::magni();
    m_VecX = m_VecX * t_Inver;
    m_VecY = m_VecY * t_Inver;
    m_VecZ = m_VecZ * t_Inver;
    return *this;
}

/********************Math operator for point*********************/

//translate a point
Point Point::operator + (const Vector &a_Vec) const
{
    return Point(m_PosX + a_Vec.getX(), m_PosY + a_Vec.getY(), m_PosZ + a_Vec.getZ());
}

Point Point::operator + (const Point &a_Pt) const
{
    return Point(m_PosX + a_Pt.getX(), m_PosY + a_Pt.getY(), m_PosZ + a_Pt.getZ());
}

Point Point::operator - (const Vector &a_Vec) const
{
    return Point(m_PosX - a_Vec.getX(), m_PosY - a_Vec.getY(), m_PosZ - a_Vec.getZ());
}

Point Point::operator - (const Point &a_Pt) const
{
    return Point(m_PosX - a_Pt.getX(), m_PosY - a_Pt.getY(), m_PosZ - a_Pt.getZ());
}

Point Point::operator / (const float &a_Num) const
{
    return Point(m_PosX / a_Num, m_PosY / a_Num, m_PosZ / a_Num);
}

Point Point::operator * (const float &a_Num) const
{
    return Point(m_PosX * a_Num, m_PosY * a_Num, m_PosZ * a_Num);
}

Vector Point::getVec(const Point& a_SrartPt, const Point& a_EndPt)
{
    return Vector(a_EndPt.getX() - a_SrartPt.getX(),
                  a_EndPt.getY() - a_SrartPt.getY(),
                  a_EndPt.getZ() - a_SrartPt.getZ());
}

Color Color::operator * (const float &a_Brightness) const
{
    return Color(m_Red * a_Brightness, m_Green * a_Brightness, m_Blue * a_Brightness);
}

Color Color::operator + (const Color &a_Color) const
{
    float t_Red   = m_Red   + a_Color.getRed();
    float t_Green = m_Green + a_Color.getGreen();
    float t_Blue  = m_Blue  + a_Color.getBlue();
    return Color(   t_Red < 255 ?   t_Red : 255,
                  t_Green < 255 ? t_Green : 255,
                   t_Blue < 255 ?  t_Blue : 255);
}
