#ifndef RECT_HPP
#define RECT_HPP

#include "engine/math.hpp"

class Rect
{
private:
    float x, y, w, h;

public:
    Rect();
    template <typename T1, typename T2, typename T3, typename T4>
    Rect(T1 x, T2 y, T3 w, T4 h)
    {
        constexpr bool all_arithmetic =
            std::is_arithmetic<T1>::value &&
            std::is_arithmetic<T2>::value &&
            std::is_arithmetic<T3>::value &&
            std::is_arithmetic<T4>::value;

        if (!all_arithmetic)
        {
            throw std::invalid_argument("Type must be arithmetic");
        }
        this->x = static_cast<float>(x);
        this->y = static_cast<float>(y);
        this->w = static_cast<float>(w);
        this->h = static_cast<float>(h);
    }
    Rect(const Rect &other);
    template <typename T>
    Rect(const std::initializer_list<T> &list)
    {
        if (list.size() != 4)
        {
            throw std::invalid_argument("Initializer list must contain exactly 4 elements.");
        }
        auto it = list.begin();
        x = static_cast<float>(*it);
        y = static_cast<float>(*(++it));
        w = static_cast<float>(*(++it));
        h = static_cast<float>(*(++it));
    }

    template <typename T>
    Rect &operator=(const std::initializer_list<T> &list)
    {
        if (list.size() != 4)
        {
            throw std::invalid_argument("Initializer list must contain exactly 4 elements.");
        }
        auto it = list.begin();
        x = static_cast<float>(*it);
        y = static_cast<float>(*(++it));
        w = static_cast<float>(*(++it));
        h = static_cast<float>(*(++it));
        return *this;
    }

    float getTop() const;
    float getBottom() const;
    float getWidth() const;
    float getHeight() const;
    float getLeft() const;
    float getRight() const;
    float getCenterX() const;
    float getCenterY() const;
    Vec2 getCenter() const;
    Vec2 getTopLeft() const;
    Vec2 getBottomLeft() const;
    Vec2 getTopRight() const;
    Vec2 getBottomRight() const;

    void setTop(const float value);
    void setBottom(const float value);
    void setWidth(const float value);
    void setHeight(const float value);
    void setLeft(const float value);
    void setRight(const float value);
    void setCenterX(const float value);
    void setCenterY(const float value);
    void setCenter(const Vec2 &pos);
    void setTopLeft(const Vec2 &pos);
    void setBottomLeft(const Vec2 &pos);
    void setTopRight(const Vec2 &pos);
    void setBottomRight(const Vec2 &pos);

    template <typename T1, typename T2>
    void setCenter(T1 x, T2 y)
    {
        static_assert(std::is_arithmetic<T1>::value, "T1 must be an arithmetic type");
        static_assert(std::is_arithmetic<T2>::value, "T2 must be an arithmetic type");
        this->x = static_cast<float>(x) - w / 2;
        this->y = static_cast<float>(y) - h / 2;
    }

    template <typename T1, typename T2>
    void setTopLeft(T1 x, T2 y)
    {
        static_assert(std::is_arithmetic<T1>::value, "T1 must be an arithmetic type");
        static_assert(std::is_arithmetic<T2>::value, "T2 must be an arithmetic type");
        this->x = static_cast<float>(x);
        this->y = static_cast<float>(y);
    }

    template <typename T1, typename T2>
    void setBottomLeft(T1 x, T2 y)
    {
        static_assert(std::is_arithmetic<T1>::value, "T1 must be an arithmetic type");
        static_assert(std::is_arithmetic<T2>::value, "T2 must be an arithmetic type");
        this->x = static_cast<float>(x);
        this->y = static_cast<float>(y) - h;
    }

    template <typename T1, typename T2>
    void setTopRight(T1 x, T2 y)
    {
        static_assert(std::is_arithmetic<T1>::value, "T1 must be an arithmetic type");
        static_assert(std::is_arithmetic<T2>::value, "T2 must be an arithmetic type");
        this->x = static_cast<float>(x) - w;
        this->y = static_cast<float>(y);
    }

    template <typename T1, typename T2>
    void setBottomRight(T1 x, T2 y)
    {
        static_assert(std::is_arithmetic<T1>::value, "T1 must be an arithmetic type");
        static_assert(std::is_arithmetic<T2>::value, "T2 must be an arithmetic type");
        this->x = static_cast<float>(x) - w;
        this->y = static_cast<float>(y) - h;
    }

    
};

#endif