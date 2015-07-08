#include "Rect.h"
#include <stdexcept>

using namespace std;

Rect::Rect(float width, float height, Point2D upperLeftCornerPosition)
{
    if (width <= 0)
    {
        throw invalid_argument("Width cannot be less than zero");
    }
    else if (height <= 0)
    {
        throw invalid_argument("Height cannot be less than zero");
    }

    m_width = width;
    m_height = height;
    m_upperLeftPoint = upperLeftCornerPosition;
}


Rect::~Rect()
{
}

Rect::Rect(const Rect &rect)
{
    m_height = rect.GetHeight();
    m_width = rect.GetWidth();
    m_upperLeftPoint = rect.GetUpperLeftPoint();
}

Rect Rect::operator=(const Rect &rect)
{
    m_height = rect.GetHeight();
    m_width = rect.GetWidth();
    m_upperLeftPoint = rect.GetUpperLeftPoint();
    return *this;
}

float Rect::GetWidth() const
{
    return m_width;
}

float Rect::GetHeight() const
{
    return m_height;
}

Point2D Rect::GetUpperLeftPoint() const
{
    return m_upperLeftPoint;
}

Point2D Rect::GetUpperRightPoint() const
{
    Point2D p = m_upperLeftPoint;
    p.x += m_width;
    return p;
}

Point2D Rect::GetLowerLeftPoint() const
{
    Point2D p = m_upperLeftPoint;
    p.y -= m_height;
    return p;
}

Point2D Rect::GetLowerRightPoint() const
{
    Point2D p = m_upperLeftPoint;
    p.y -= m_height;
    p.x += m_width;
    return p;
}

bool Rect::AxisAlignedCollision(Rect rect)
{
    if (GetUpperLeftPoint().x <= rect.GetUpperRightPoint().x && GetUpperRightPoint().x >= rect.GetUpperLeftPoint().x)
    {
        if (GetLowerLeftPoint().y <= rect.GetUpperLeftPoint().y && GetUpperLeftPoint().y >= rect.GetLowerLeftPoint().y)
        {
            return true;
        }
    }
    return false;
}

bool Rect::AxisAlignedCollision(Point2D point)
{
    if (GetUpperLeftPoint().x <= point.x && GetUpperRightPoint().x >= point.x)
    {
        if (GetLowerLeftPoint().y <= point.y && GetUpperLeftPoint().y >= point.y)
        {
            return true;
        }
    }
    return false;
}