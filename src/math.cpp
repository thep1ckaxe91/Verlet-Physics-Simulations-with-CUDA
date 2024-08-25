#include "math.hpp"
#include "cmath"

Vec2::Vec2()
{
    this->x = this->y = 0;
}

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vec2::Vec2(const Vec2 &other)
{
    this->x = other.x;
    this->y = other.y;
}

Vec2 Vec2::operator+(const Vec2 &other) const
{
    return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const
{
    return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(const float scalar) const
{
    return Vec2(x * scalar, y * scalar);
}

Vec2 Vec2::operator/(const float scalar) const
{
    return Vec2(x / scalar, y / scalar);
}

Vec2 operator*(const float scalar, const Vec2 &v)
{
    return Vec2(v.x * scalar, v.y * scalar);
}

Vec2 &Vec2::operator+=(const Vec2 &other)
{
    x += other.x;
    y += other.y;
    return *this;
}
Vec2 &Vec2::operator-=(const Vec2 &other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}
Vec2 &Vec2::operator*=(const float scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}
Vec2 &Vec2::operator/=(const float scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

float Vec2::length() const
{
    return sqrt(x * x + y * y);
}

float Vec2::sqr_length() const
{
    return x * x + y * y;
}

void Vec2::scale_to_length(const float length)
{
    if (length <= 0)
        throw "Length must be positive";
    const float len = this->length();
    x *= length / len;
    y *= length / len;
}

Vec2 Vec2::normalize() const
{
    return (*this) / this->length();
}

Vec2 &Vec2::normalize_ip()
{
    return (*this) /= this->length();
}

float Vec2::dot(const Vec2 &other) const
{
    return x * other.x + y * other.y;
}

Vec2 Vec2::project(const Vec2 &normal) const
{
    return normal * (this->dot(normal) / normal.sqr_length());
}
Vec2 &Vec2::project_ip(const Vec2 &normal)
{
    return *this = normal * (this->dot(normal) / normal.sqr_length());
}

Vec2 Vec2::reflect(const Vec2 &normal) const
{
    return *this - normal * 2 * (this->dot(normal));
}

Vec2 &Vec2::reflect_ip(const Vec2 &normal)
{
    return *this -= normal * 2 * (this->dot(normal));
}

Vec2 Vec2::rotate(const float degree) const
{
    const float rad = degree / 180 * M_PI;
    return Vec2(
        x * cos(rad) - y * sin(rad),
        x * sin(rad) + y * cos(rad));
}

Vec2 &Vec2::rotate_ip(const float degree)
{
    const float rad = degree / 180 * M_PI;
    this->x = x * cos(rad) - y * sin(rad);
    this->y = x * sin(rad) + y * cos(rad);
    return *this;
}

Vec2 Vec2::lerp(const Vec2 &other, const float w) const
{
    if (w < 0 || w > 1)
    {
        throw "Weight must be in range [0,1]";
    }
    return (*this) + w * (other - (*this));
}
Vec2 Vec2::move_towards(const Vec2 &other, const float distance) const
{
    Vec2 tmp = other - *this;
    return (*this) + tmp * (distance / tmp.length());
}
Vec2 Vec2::move_towards_ip(const Vec2 &other, const float distance)
{
    Vec2 tmp = other - *this;
    return (*this) += tmp * (distance / tmp.length());
}

float clamp(const float value, const float min, const float max)
{
    return (value < min ? min : (value > max ? max : value));
}

float lerp(const float a, const float b, const float w)
{
    if (w < 0 || w > 1)
    {
        throw "Weight must be in range [0,1]";
    }
    return b * w - a * (1 - w);
}

