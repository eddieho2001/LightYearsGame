#include "framework/MathUtility.h"

namespace ly {
    const float PI = 3.141592653589793;
}

sf::Vector2f ly::Rotation2Vecor(float rotation)
{
    float radian = Degree2Radian(rotation);
    return sf::Vector2f(std::cos(radian), std::sin(radian));
}

float ly::Degree2Radian(float degree)
{
    return degree * (PI / 180.f);
}

float ly::Radian2Degree(float rad)
{
    return rad * (180.f / PI);
}
