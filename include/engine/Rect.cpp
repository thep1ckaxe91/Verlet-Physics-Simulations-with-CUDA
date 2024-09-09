#include "engine/Rect.hpp"

Rect::Rect() : x(0), y(0), w(0), h(0) {}
Rect::Rect(const Rect &other) : x(other.x), y(other.y), w(other.w), h(other.h) {}
Rect::Rect(const Vec2 &topleft, const Vec2 &size) : x(topleft.x), y(topleft.y), w(size.x), h(size.y) {}

bool Rect::operator==(const Rect &other)
{
    return x == other.getLeft() and y == other.getTop() and w == other.getWidth() and h == other.getHeight();
}

bool Rect::operator==(Rect&& other)
{
    return x == other.getLeft() and y == other.getTop() and w == other.getWidth() and h == other.getHeight();
} 

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

Vec2 Rect::getSize() const
{
    return Vec2(w, h);
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

void Rect::setSize(const Vec2 &size)
{
    w = size.x;
    h = size.y;
}

std::ostream &operator<<(std::ostream &out, const Rect &r)
{
    out << "Rect(" << r.x << "," << r.y << "," << r.w << "," << r.h << ")";
    return out;
}

Rect Rect::move(float dx, float dy) const
{
    return Rect(x + dx, y + dy, w, h);
}

Rect &Rect::move_ip(float dx, float dy)
{
    x += dx;
    y += dy;
    return *this;
}
Rect Rect::inflate(float dw, float dh) const
{
    float new_w = w + dw;
    float new_h = h + dh;
    float new_x = x - (new_w - w) / 2;
    float new_y = y - (new_h - h) / 2;
    return Rect(new_x, new_y, new_w, new_h);
}

Rect &Rect::inflate(float dw, float dh)
{
    w += dw;
    h += dh;
    x -= dw / 2;
    y -= dh / 2;
    return *this;
}
Rect Rect::scale_by(float scalarx, float scalary) const
{
    float new_w = w * scalarx;
    float new_h = h * scalary;
    float new_x = x + (w - new_w) / 2;
    float new_y = y + (h - new_h) / 2;
    return Rect(new_x, new_y, new_w, new_h);
}

Rect &Rect::scale_by_ip(float scalarx, float scalary)
{
    w *= scalarx;
    h *= scalary;
    x += (w - (w * scalarx)) / 2;
    y += (h - (h * scalary)) / 2;
    return *this;
}

Rect Rect::scale_by(const Vec2 &scalar) const
{
    return scale_by(scalar.x, scalar.y);
}

Rect &Rect::scale_by_ip(const Vec2 &scalar)
{
    return scale_by_ip(scalar.x, scalar.y);
}
Rect Rect::clamp(const Rect &other) const
{
    float new_x = std::max(x, other.x);
    float new_y = std::max(y, other.y);
    float new_right = std::min(x + w, other.x + other.w);
    float new_bottom = std::min(y + h, other.y + other.h);

    if (new_right > new_x && new_bottom > new_y)
    {
        return Rect(new_x, new_y, new_right - new_x, new_bottom - new_y);
    }
    return Rect(); // Return an empty rectangle if no overlap
}

Rect Rect::clamp(Rect &&other) const
{
    return clamp(other);
}

Rect &Rect::clamp_ip(const Rect &other)
{
    *this = clamp(other);
    return *this;
}

Rect &Rect::clamp_ip(Rect &&other)
{
    return clamp_ip(other);
}

Rect Rect::clip(const Rect &other) const
{
    float new_x = std::max(x, other.x);
    float new_y = std::max(y, other.y);
    float new_right = std::min(x + w, other.x + other.w);
    float new_bottom = std::min(y + h, other.y + other.h);

    if (new_right > new_x && new_bottom > new_y)
    {
        return Rect(new_x, new_y, new_right - new_x, new_bottom - new_y);
    }
    return Rect(); // Return an empty rectangle if no overlap
}

std::pair<Vec2, Vec2> Rect::clipline(const Vec2 &start, const Vec2 &end) const
{
    // Clip using Liang-Barsky algorithm
    auto clip = [](float p, float q, float &t0, float &t1)
    {
        float r = q / p;
        if (p < 0)
        {
            if (r > t1)
                return false;
            if (r > t0)
                t0 = r;
        }
        else if (p > 0)
        {
            if (r < t0)
                return false;
            if (r < t1)
                t1 = r;
        }
        else if (q < 0)
        {
            return false;
        }
        return true;
    };

    float t0 = 0.0f;
    float t1 = 1.0f;

    float dx = end.x - start.x;
    float dy = end.y - start.y;

    if (!clip(-dx, start.x - x, t0, t1) ||
        !clip(dx, (x + w) - start.x, t0, t1) ||
        !clip(-dy, start.y - y, t0, t1) ||
        !clip(dy, (y + h) - start.y, t0, t1))
    {
        return {Vec2(0, 0), Vec2(0, 0)};
    }

    Vec2 new_start = start + (end - start) * t0;
    Vec2 new_end = start + (end - start) * t1;

    return {new_start, new_end};
}

std::pair<Vec2, Vec2> Rect::clipline(float xs, float ys, const Vec2 &end) const
{
    return clipline(Vec2(xs, ys), end);
}

std::pair<Vec2, Vec2> Rect::clipline(const Vec2 &start, float xe, float ye) const
{
    return clipline(start, Vec2(xe, ye));
}

std::pair<Vec2, Vec2> Rect::clipline(float xs, float ys, float xe, float ye) const
{
    return clipline(Vec2(xs, ys), Vec2(xe, ye));
}

Rect Rect::fit(const Rect &other) const
{
    float aspect_ratio = w / h;
    float new_w, new_h;

    if (other.w / other.h > aspect_ratio)
    {
        new_w = other.w;
        new_h = new_w / aspect_ratio;
    }
    else
    {
        new_h = other.h;
        new_w = new_h * aspect_ratio;
    }

    float new_x = other.x + (other.w - new_w) / 2;
    float new_y = other.y + (other.h - new_h) / 2;
    return Rect(new_x, new_y, new_w, new_h);
}

void Rect::normalize()
{
    if (w < 0)
    {
        x += w;
        w = -w;
    }
    if (h < 0)
    {
        y += h;
        h = -h;
    }
}
bool Rect::contains(const Rect &other) const
{
    return x <= other.x && y <= other.y &&
           (x + w) >= (other.x + other.w) &&
           (y + h) >= (other.y + other.h);
}
bool Rect::collidepoint(const Vec2 &p) const
{
    return p.x > x && p.y > y && p.x < (x + w) && p.y < (y + h);
}

bool Rect::collidepoint(float x, float y) const
{
    return collidepoint(Vec2(x, y));
}

bool Rect::colliderect(const Rect &other) const
{
    return !(other.getLeft() > getRight() ||
             other.getRight() < getLeft() ||
             other.getTop() > getBottom() ||
             other.getBottom() < getTop());
}
