#include "Utils.hpp"

#include <cmath>

float getRandFloat(float min, float max)
{
    int range = (max-min)*1000;
    if (!range) return 0.0f;
    return min+(std::rand()%range)*0.001f;
}

float getRandomAngle()
{
    return 0.0f;
}

float getRandomAngle(float min, float max)
{
    int range = 1000.0*(max-min);

    if (range)
    {
        float angle = (rand()%range)*0.001;
        return angle+min;
    }

    return 0.0f;
}

float getAngleFromVec(const sf::Vector2i& v)
{
    float result;
    float ax = v.x;
    float ay = v.y;
    float anorm = sqrt(ax*ax+ay*ay);

    result = acos(ax/anorm);

    result = ay < 0 ? -result : result;

    return result;
}

float sign(float f)
{
    return f<0.0f?-1.f:1.0f;
}

Vec2 transformVec(const Vec2& v, float r, Vec2 t)
{
    float cosa = cos(r);
    float sina = sin(r);

    return Vec2(v.x*cosa-v.y*sina+t.x, v.x*sina+v.y*cosa+t.y);
}

