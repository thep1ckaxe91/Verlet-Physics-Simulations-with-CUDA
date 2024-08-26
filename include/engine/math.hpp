#pragma once
#ifndef VEC2_HPP
#define VEC2_HPP

#define M_PI 3.14159265358979323846264338327950288
#include<ostream>

struct Vec2
{
    float x;
    float y;

    Vec2();
    Vec2(float x, float y);
    Vec2(const Vec2 &other);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;

    Vec2 &operator+=(const Vec2 &other);
    Vec2 &operator-=(const Vec2 &other);
    Vec2 &operator*=(const float scalar);
    Vec2 &operator/=(const float scalar);

    float length() const;
    float sqr_length() const;
    float dot(const Vec2 &other) const;
    float cross(const Vec2 &other) const;

    void scale_to_length(const float length);

    Vec2 normalize() const;
    Vec2 &normalize_ip();

    Vec2 project(const Vec2 &normal) const;
    Vec2 &project_ip(const Vec2 &normal);

    Vec2 reflect(const Vec2 &normal) const;
    Vec2 &reflect_ip(const Vec2 &normal);

    /**
     * @brief rotate a vector counter-clockwise
     *
     * @param degree
     * @return new Vec2 that got rotated from this vector
     */
    Vec2 rotate(const float degree) const;
    Vec2 &rotate_ip(const float degree);

    Vec2 lerp(const Vec2 &other, const float w) const;
    Vec2 move_towards(const Vec2 &other, const float distance) const;
    Vec2 move_towards_ip(const Vec2 &other, const float distance);

    /**
     * @brief angle to another vector counter clockwise
     * 
     * @param other other vector
     * @return float result in degree
     */
    float angle_to(const Vec2 &other) const;

    friend std::ostream& operator << (std::ostream &out, const Vec2& other);

};

Vec2 operator*(const float scalar, const Vec2 &v);

float clamp(const float value, const float min, const float max);

float lerp(const float a, const float b, const float w);

#endif