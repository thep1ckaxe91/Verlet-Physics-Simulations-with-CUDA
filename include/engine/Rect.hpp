#ifndef RECT_HPP
#define RECT_HPP

#include "engine/math.hpp"
#include <ostream>
#include <vector>

class Rect
{
private:
    float x, y, w, h;

public:
    Rect();
    Rect(const Vec2 &topleft, const Vec2 &size);
    template <typename T1, typename T2>
    Rect(const Vec2 &topleft, T1 w, T2 h)
    {
        static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, "Type must be arithmetic");
        this->w = static_cast<float>(w);
        this->h = static_cast<float>(h);
    }
    template <typename T1, typename T2>
    Rect(T1 x, T2 y, const Vec2 &size)
    {
        static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, "Type must be arithmetic");
        this->x = static_cast<float>(x);
        this->y = static_cast<float>(y);
    }
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
        if (list.size() == 0)
        {
            x = y = w = h = 0;
            return;
        }
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
        if (list.size() == 0)
        {
            x = y = w = h = 0;
            return *this;
        }
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

    template <typename T>
    bool operator==(const std::initializer_list<T> &list)
    {
        if (list.size() > 4)
            return false;
        if (list.size() == 0)
            return x == 0 and y == 0 and w == 0 and h == 0;
        auto it = list.begin();
        if(x != *it) return false;
        if(y != *(++it)) return false;
        if(w != *(++it)) return false;
        if(h != *(++it)) return false;
        return true;
    }

    bool operator==(const Rect& other);
    bool operator==(Rect&& other);

    friend std::ostream &operator<<(std::ostream &out, const Rect &r);

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
    Vec2 getSize() const;

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
    void setSize(const Vec2 &size);
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

    /*Returns a new rectangle that is moved by the given offset. The x and y arguments can be any integer value, positive or negative.*/
    Rect move(float dx, float dy) const;
    Rect &move_ip(float dx, float dy);
    /*Returns a new rectangle with the size changed by the given offset. The rectangle remains centered around its current center. Negative values will shrink the rectangle.*/
    Rect inflate(float dw, float dh) const;
    Rect &inflate(float dw, float dh);
    /*
    Returns a new rectangle with the size scaled by the given multipliers. The rectangle remains centered around its current center. A single scalar or separate width and height scalars are allowed. Values above one will increase the size of the rectangle, whereas values between zero and one will decrease the size of the rectangle.
     */
    Rect scale_by(float scalarx, float scalary) const;
    Rect &scale_by_ip(float scalarx, float scalary);
    Rect scale_by(const Vec2 &scalar) const;
    Rect &scale_by_ip(const Vec2 &scalar);
    /*Returns a new rectangle that is moved to be completely inside the argument Rect. If the rectangle is too large to fit inside, it is centered inside the argument Rect, but its size is not changed.*/
    Rect clamp(const Rect &other) const;
    Rect clamp(Rect &&other) const;
    Rect &clamp_ip(const Rect &other);
    Rect &clamp_ip(Rect &&other);
    /*Returns a new rectangle that is cropped to be completely inside the argument Rect. If the two rectangles do not overlap to begin with, a Rect with 0 size is returned.*/
    Rect clip(const Rect &other) const;
    /*Returns the coordinates of a line that is cropped to be completely inside the rectangle. If the line does not overlap the rectangle, then an tuple with 2 Vec2::zero is returned.*/
    std::pair<Vec2, Vec2> clipline(const Vec2 &start, const Vec2 &end) const;
    std::pair<Vec2, Vec2> clipline(float xs, float ys, const Vec2 &end) const;
    std::pair<Vec2, Vec2> clipline(const Vec2 &start, float xe, float ye) const;
    std::pair<Vec2, Vec2> clipline(float xs, float ys, float xe, float ye) const;

    /*Returns a new rectangle that is moved and resized to fit another. The aspect ratio of the original Rect is preserved, so the new rectangle may be smaller than the target in either width or height.*/
    Rect fit(const Rect &other) const;
    /*This will flip the width or height of a rectangle if it has a negative size. The rectangle will remain in the same place, with only the sides swapped. */
    void normalize();
    /*Returns true when the argument is completely inside the Rect.*/
    bool contains(const Rect &other) const;
    /*Returns true if the given point is inside the rectangle. A point along the right or bottom edge is not considered to be inside the rectangle.*/
    bool collidepoint(const Vec2 &p) const;
    bool collidepoint(float x, float y) const;
    bool colliderect(const Rect &other) const;

    template <typename Container>
    auto collidelist(const Container &r_list) const -> std::enable_if_t<
                                                        std::is_same<typename Container::value_type, Rect>::value ||
                                                            std::is_same<typename Container::value_type, const Rect>::value,
                                                        bool>
    {
        for (auto &r : r_list)
        {
            if (this->colliderect(r))
                return true;
        }
        return false;
    }
    template <typename Container>
    auto collidelistall(const Container &r_list) const -> std::enable_if_t<
                                                           std::is_same<typename Container::value_type, Rect>::value ||
                                                               std::is_same<typename Container::value_type, const Rect>::value,
                                                           std::vector<Rect>>
    {
        std::vector<Rect> res;
        for (auto &r : r_list)
        {
            if (this->colliderect(r))
                res.push_back(r);
        }
        return res;
    }
    template <typename T, typename RectExtractorFunc>
    bool collideobject(const T &object, RectExtractorFunc ex) const
    {
        return this->colliderect(ex(object));
    }
    template <typename T, typename RectExtractorFunc>
    std::vector<int> collideobjectall(const std::vector<T> &objects, RectExtractorFunc ex) const
    {
        std::vector<int> res;
        int id = 0;
        for (auto &o : objects)
        {
            if (this->collideobject(o, ex))
                res.push_back(id);
            id++;
        }
        return res;
    }
};

#endif