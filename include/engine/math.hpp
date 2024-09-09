#pragma once
#ifndef MATH_HPP
#define MATH_HPP

#define M_PI 3.14159265358979323846264338327950288
#include <ostream>
struct Vec3;
struct Vec2
{
    float x;
    float y;

    const static Vec2 unit_x;
    const static Vec2 unit_y;
    const static Vec2 zero;

    Vec2();
    template <typename T1, typename T2>
    Vec2(T1 x, T2 y)
    {
        if (!std::is_arithmetic_v<T1> or !std::is_arithmetic_v<T2>)
            throw std::invalid_argument("Type must be arithmetic");
        this->x = x;
        this->y = y;
    }
    Vec2(const Vec2 &other);
    Vec2(const Vec3 &v);
    template <typename T>
    Vec2(const std::initializer_list<T> &list)
    {
        if (!std::is_arithmetic<T>::value)
            throw std::invalid_argument("Type must be arithmetic");
        if (list.size() != 2)
        {
            throw std::invalid_argument("Vec2 initializer list must have exactly 2 elements");
        }

        auto it = list.begin();
        x = static_cast<float>(*it);
        y = static_cast<float>(*(++it));
    }
    template <typename T>
    bool operator==(const std::initializer_list<T> &list)
    {
        if (list.size() > 2)
            return false;
        if (list.size() == 0)
            return x == 0 and y == 0;
        auto it = list.begin();
        if (x != *it)
            return false;
        if (y != *(++it))
            return false;
        return true;
    }
    bool operator==(const Vec2 &other);

    Vec2 operator+(const Vec2 &other) const;
    Vec2 operator-(const Vec2 &other) const;
    Vec2 operator*(const float scalar) const;
    Vec2 operator/(const float scalar) const;
    Vec2 operator-() const;
    template <typename T>
    Vec2 &operator=(const std::initializer_list<T> &list)
    {
        if (!std::is_arithmetic<T>::value)
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

    float distance_to(const Vec2 &other) const;
    float distance_sqr_to(const Vec2 &other) const;

    Vec2 clamp_magnitude(const float max_len) const;
    Vec2 clamp_magnitude(const float min_len, const float max_len) const;

    Vec2 &clamp_magnitude_ip(const float max_len);
    Vec2 &clamp_magnitude_ip(const float min_len, const float max_len);

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
    template <typename T1, typename T2, typename T3>
    Vec3(T1 x, T2 y, T3 z)
    {
        if (!std::is_arithmetic_v<T1> || !std::is_arithmetic_v<T2> || !std::is_arithmetic_v<T3>)
            throw std::invalid_argument("Type must be arithmetic");
        this->x = x;
        this->y = y;
        this->z = z;
    }
    Vec3(const Vec3 &other);
    Vec3(const Vec2 &v);
    template <typename T>
    Vec3(const std::initializer_list<T> &list)
    {
        if (list.size() == 0)
        {
            x = y = z = 0;
            return;
        }
        if (!std::is_arithmetic<T>::value)
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

    Vec3 operator+(const Vec3 &other) const;
    Vec3 operator-(const Vec3 &other) const;
    Vec3 operator*(const float scalar) const;
    Vec3 operator/(const float scalar) const;
    Vec3 operator-() const;
    template <typename T>
    Vec3 &operator=(const std::initializer_list<T> &list)
    {
        if (list.size() == 0)
        {
            x = y = z = 0;
            return *this;
        }
        if (!std::is_arithmetic<T>::value)
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

    template <typename T>
    bool operator==(const std::initializer_list<T> &list)
    {
        if (list.size() > 3)
            return false;
        if (list.size() == 0)
            return x == 0 and y == 0 and z == 0;
        auto it = list.begin();
        if (x != *it)
            return false;
        if (y != *(++it))
            return false;
        if (z != *(++it))
            return false;
        
        return true;
    }
    bool operator==(const Vec3 &other);

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

    float distance_to(const Vec3 &other) const;
    float distance_sqr_to(const Vec3 &other) const;

    Vec3 clamp_magnitude(const float max_len) const;
    Vec3 clamp_magnitude(const float min_len, const float max_len) const;

    Vec3 &clamp_magnitude_ip(const float max_len);
    Vec3 &clamp_magnitude_ip(const float min_len, const float max_len);

    Vec3 rotate(const float degree, const Vec3 &axis) const;
    Vec3 &rotate_ip(const float degree, const Vec3 &axis);

    Vec3 rotate_rad(const float rad, const Vec3 &axis) const;
    Vec3 &rotate_rad_ip(const float rad, const Vec3 &axis);

    Vec3 rotate_x(const float degree) const;
    Vec3 &rotate_x_ip(const float degree);
    Vec3 rotate_y(const float degree) const;
    Vec3 &rotate_y_ip(const float degree);
    Vec3 rotate_z(const float degree) const;
    Vec3 &rotate_z_ip(const float degree);

    Vec3 rotate_rad_x(const float rad) const;
    Vec3 &rotate_x_rad_ip(const float rad);
    Vec3 rotate_rad_y(const float rad) const;
    Vec3 &rotate_y_rad_ip(const float rad);
    Vec3 rotate_rad_z(const float rad) const;
    Vec3 &rotate_z_rad_ip(const float rad);

    // return smaller angle to the vector
    float angle_to(const Vec3 &v) const;

    friend std::ostream &operator<<(std::ostream &out, const Vec3 &other);
};

Vec2 operator*(const float scalar, const Vec2 &v);

Vec3 operator*(const float scalar, const Vec3 &v);

float clamp(const float value, const float min, const float max);

float lerp(const float a, const float b, const float w);

#endif