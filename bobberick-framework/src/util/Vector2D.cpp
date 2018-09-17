//
// Created by Mike Rovers on 30/08/2018.
//

#include <cmath>
#include "Vector2D.h"

float Vector2D::length() {
    return sqrt((m_x * m_x) + (m_y * m_y));
}

void Vector2D::normalize() {
    float l = length();
    if (l > 0) {
        (*this) *= 1 / l;
    }
}

Vector2D &Vector2D::Zero()
{
    setX(0);
    setY(0);

    return *this;
}
