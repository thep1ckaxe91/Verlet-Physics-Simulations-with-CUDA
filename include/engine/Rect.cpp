#include "engine/Rect.hpp"

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(const Rect &other) : x(other.x), y(other.y), w(other.w), h(other.h) {}

float Rect::getTop() const
{
    return y;
}

float Rect::getBottom() const
{
    return y + h;
}

float Rect::getWidth() const
{
    return w;
}

float Rect::getHeight() const
{
    return h;
}

float Rect::getLeft() const
{
    return x;
}

float Rect::getRight() const
{
    return x + w;
}

float Rect::getCenterX() const
{
    return x + w / 2;
}

float Rect::getCenterY() const
{
    return y + h / 2;
}

Vec2 Rect::getCenter() const
{
    return Vec2(getCenterX(), getCenterY());
}

Vec2 Rect::getTopLeft() const
{
    return Vec2(x, y);
}

Vec2 Rect::getBottomLeft() const
{
    return Vec2(x, getBottom());
}

Vec2 Rect::getTopRight() const
{
    return Vec2(getRight(), y);
}

Vec2 Rect::getBottomRight() const
{
    return Vec2(getRight(), getBottom());
}

void Rect::setTop(float value)
{
    y = value;
}

void Rect::setBottom(float value)
{
    y = value - h;
}

void Rect::setWidth(float value)
{
    w = value;
}

void Rect::setHeight(float value)
{
    h = value;
}

void Rect::setLeft(float value)
{
    x = value;
}

void Rect::setRight(float value)
{
    x = value - w;
}

void Rect::setCenterX(float value)
{
    x = value - w / 2;
}

void Rect::setCenterY(float value)
{
    y = value - h / 2;
}

void Rect::setCenter(const Vec2 &pos)
{
    setCenterX(pos.x);
    setCenterY(pos.y);
}

void Rect::setTopLeft(const Vec2 &pos)
{
    x = pos.x;
    y = pos.y;
}

void Rect::setBottomLeft(const Vec2 &pos)
{
    x = pos.x;
    y = pos.y - h;
}

void Rect::setTopRight(const Vec2 &pos)
{
    x = pos.x - w;
    y = pos.y;
}

void Rect::setBottomRight(const Vec2 &pos)
{
    x = pos.x - w;
    y = pos.y - h;
}
