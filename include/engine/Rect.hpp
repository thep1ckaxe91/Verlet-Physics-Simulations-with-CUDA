#ifndef RECT_HPP
#define RECT_HPP

#include "math.hpp"

class Rect
{
private:
    float x, y, w, h;
public:
    Rect();
    Rect(float x, float y, float w, float h);
    Rect(const Rect& other);

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

    void setTop(float value) const;
    void setBottom(float value) const;
    void setWidth(float value) const;
    void setHeight(float value) const;
    void setLeft(float value) const;
    void setRight(float value) const;
    void setCenterX(float value) const;
    void setCenterY(float value) const;
    void setCenter(Vec2 pos) const;
    void setTopLeft(Vec2 pos) const;
    void setBottomLeft(Vec2 pos) const;
    void setTopRight(Vec2 pos) const;
    void setBottomRight(Vec2 pos) const;
    
    
};

#endif