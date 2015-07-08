#pragma once

#include "VectorMath.h"

class Rect
{
public:
    Rect(float width, float height, Point2D upperLeftCornerPosition);
    ~Rect();
    Rect(const Rect &rect);
    Rect operator=(const Rect &rect);

    float GetWidth() const;
    float GetHeight() const;
    Point2D GetUpperLeftPoint() const;
    Point2D GetUpperRightPoint() const;
    Point2D GetLowerLeftPoint() const;
    Point2D GetLowerRightPoint() const;

    bool AxisAlignedCollision(Rect rect);
    bool AxisAlignedCollision(Point2D point);

private:
    float m_width;
    float m_height;
    Point2D m_upperLeftPoint;
};

