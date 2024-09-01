#pragma once
#ifndef VEC2_HPP
#define VEC2_HPP

#define M_PI 3.14159265358979323846264338327950288
#include <ostream>

struct Vec2
{
    float x;
    float y;

    const static Vec2 unit_x;
    const static Vec2 unit_y;
    const static Vec2 zero;

    Vec2();
    Vec2(float x, float y);
    template <typename T>
    inline Vec2(const std::initializer_list<T> &list)
    {
        if(!std::is_arithmetic<T>::value)
            throw std::invalid_argument("Type must be arithmetic");
        if (list.size() != 2)
        {
            throw std::invalid_argument("Vec2 initializer list must have exactly 2 elements");
        }

        auto it = list.begin();
        x = static_cast<float>(*it++);
        y = static_cast<float>(*it);
    }
    Vec2(const Vec2 &other);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;
    Vec2 operator-() const;
    template <typename T>
    Vec2 &operator=(const std::initializer_list<T> &list)
    {
        if(!std::is_arithmetic<T>::value)
            throw std::invalid_argument("Type must be arithmetic");
        if (list.size() != 2)
            throw std::invalid_argument("Vec2 initializer list must have exactly 2 elements");
        auto it = list.begin();
        x = static_cast<float>(*it++);
        y = static_cast<float>(*it);
        return *this;
    }
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

    friend std::ostream &operator<<(std::ostream &out, const Vec2 &other);
};

struct Vec3
{
    float x;
    float y;
    float z;

    const static Vec3 unit_x;
    const static Vec3 unit_y;
    const static Vec3 unit_z;
    const static Vec3 zero;

    Vec3();
    Vec3(float x, float y, float z);
    template <typename T>
    inline Vec3(const std::initializer_list<T> &list)
    {
        if(!std::is_arithmetic<T>::value)
            throw std::invalid_argument("Type must be arithmetic");
        if (list.size() != 3)
        {
            throw std::invalid_argument("Vec3 initializer list must have exactly 3 elements");
        }

        auto it = list.begin();
        x = static_cast<float>(*it++);
        y = static_cast<float>(*it++);
        z = static_cast<float>(*it);
    }
    Vec3(const Vec3 &other);

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(const float scalar) const;
    Vec3 operator/(const float scalar) const;
    Vec3 operator-() const;
    template <typename T>
    Vec3 &operator=(const std::initializer_list<T> &list)
    {
        if(!std::is_arithmetic<T>::value)
            throw std::invalid_argument("Type must be arithmetic");
        if (list.size() != 3)
            throw std::invalid_argument("Vec3 initializer list must have exactly 3 elements");
        
        auto it = list.begin();
        x = static_cast<float>(*it++);
        y = static_cast<float>(*it++);
        z = static_cast<float>(*it);
        return *this;
    }
    Vec3 &operator+=(const Vec3 &other);
    Vec3 &operator-=(const Vec3 &other);
    Vec3 &operator*=(const float scalar);
    Vec3 &operator/=(const float scalar);

    float length() const;
    float sqr_length() const;
    float dot(const Vec3 &other) const;
    Vec3 cross(const Vec3 &other) const;

    void scale_to_length(const float length);

    Vec3 normalize() const;
    Vec3 &normalize_ip();

    Vec3 project(const Vec3 &normal) const;
    Vec3 &project_ip(const Vec3 &normal);

    Vec3 reflect(const Vec3 &normal) const;
    Vec3 &reflect_ip(const Vec3 &normal);

    Vec3 lerp(const Vec3 &other, const float w) const;
    Vec3 move_towards(const Vec3 &other, const float distance) const;
    Vec3 move_towards_ip(const Vec3 &other, const float distance);

    /**
     * @brief angle to another vector counter clockwise
     *
     * @param other other vector
     * @return float result in degree
     */
    float angle_to(const Vec3 &other) const;

    friend std::ostream &operator<<(std::ostream &out, const Vec3 &other);
};

Vec2 operator*(const float scalar, const Vec2 &v);

Vec3 operator*(const float scalar, const Vec3 &v);

float clamp(const float value, const float min, const float max);

float lerp(const float a, const float b, const float w);

#endif