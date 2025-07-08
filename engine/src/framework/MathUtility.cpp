#include<random>
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

float ly::LerpFloat(float a, float b, float alpha) {
    if (alpha > 1.0f) alpha = 1.0f;
    if (alpha < epsilon) alpha = 0.f;
    return a + (b - a) * alpha;
}

sf::Color ly::LerpColor(const sf::Color& a, const sf::Color& b, float alpha) {
    int lerpR = LerpFloat(a.r, b.r, alpha);
    int lerpG = LerpFloat(a.g, b.g, alpha);
    int lerpB = LerpFloat(a.b, b.b, alpha);
    int lerpA = LerpFloat(a.a, b.a, alpha);

    return sf::Color(lerpR, lerpG, lerpB, lerpA);
}

sf::Vector2f ly::LerpVector(const sf::Vector2f& a, const sf::Vector2f& b, float alpha) {
    float lerpX = LerpFloat(a.x, b.x, alpha);
    float lerpY = LerpFloat(a.y, b.y, alpha);
    return sf::Vector2f{ lerpX , lerpY };
}

float ly::RandomRange(float minValue, float maxValue) {
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> real_distrib{ minValue, maxValue };
    return real_distrib(engine);
}

sf::Vector2f ly::GetRandomUnitVector()
{
    sf::Vector2f randVec{ RandomRange (-1,1), RandomRange (-1,1)};
    return Normalize(randVec);
}
