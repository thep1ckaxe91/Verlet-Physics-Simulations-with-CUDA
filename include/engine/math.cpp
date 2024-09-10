#include "engine/math.hpp"
#include "cmath"

Vec2::Vec2() : SDL_FPoint{0, 0} {}

Vec2::Vec2(const Vec2 &other) : SDL_FPoint{other.x, other.y} {}

Vec2::Vec2(const Vec3 &v) : SDL_FPoint{v.x, v.y} {}

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

Vec2 Vec2::operator-() const
{
    return Vec2(-this->x, -this->y);
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

bool Vec2::operator==(const Vec2 &other)
{
    return x == other.x and y == other.y;
}
float Vec2::length() const
{
    return std::sqrt(x * x + y * y);
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
    *this /= this->length();
    return *this;
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
    *this = normal * (this->dot(normal) / normal.sqr_length());
    return *this;
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
        throw std::invalid_argument("Weight must be in range [0,1]");
    }
    return (1 - w) * (*this) + w * other;
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

float lerp(const float v0, const float v1, const float w)
{
    if (w < 0 || w > 1)
    {
        throw std::invalid_argument("Weight must be in range [0,1]");
    }
    return (1 - w) * v0 + w * v1;
}

float Vec2::cross(const Vec2 &other) const
{
    return x * other.y - y * other.x;
}

float Vec2::angle_to(const Vec2 &other) const
{
    if (this->cross(other) >= 0)
        return acos(this->dot(other) / this->length() / other.length());
    return 360 - acos(this->dot(other) / this->length() / other.length());
}

float Vec2::distance_to(const Vec2 &other) const
{
    return std::sqrt(distance_sqr_to(other));
}

// Squared distance to another Vec2
float Vec2::distance_sqr_to(const Vec2 &other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    return dx * dx + dy * dy;
}

// Clamp magnitude to a maximum length
Vec2 Vec2::clamp_magnitude(const float max_len) const
{
    float len = std::sqrt(x * x + y * y);
    if (len > max_len)
    {
        float scale = max_len / len;
        return Vec2(x * scale, y * scale);
    }
    return *this;
}

// Clamp magnitude between min and max lengths
Vec2 Vec2::clamp_magnitude(const float min_len, const float max_len) const
{
    float len = std::sqrt(x * x + y * y);
    if (len < min_len)
    {
        float scale = min_len / len;
        return Vec2(x * scale, y * scale);
    }
    else if (len > max_len)
    {
        float scale = max_len / len;
        return Vec2(x * scale, y * scale);
    }
    return *this;
}

// In-place clamp magnitude to a maximum length
Vec2 &Vec2::clamp_magnitude_ip(const float max_len)
{
    float len = std::sqrt(x * x + y * y);
    if (len > max_len)
    {
        float scale = max_len / len;
        x *= scale;
        y *= scale;
    }
    return *this;
}

// In-place clamp magnitude between min and max lengths
Vec2 &Vec2::clamp_magnitude_ip(const float min_len, const float max_len)
{
    float len = std::sqrt(x * x + y * y);
    if (len < min_len)
    {
        float scale = min_len / len;
        x *= scale;
        y *= scale;
    }
    else if (len > max_len)
    {
        float scale = max_len / len;
        x *= scale;
        y *= scale;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &out, const Vec2 &other)
{
    out << "Vec2(" << other.x << "," << other.y << ")";
    return out;
}
const Vec2 Vec2::unit_x = Vec2(1, 0);
const Vec2 Vec2::unit_y = Vec2(0, 1);
const Vec2 Vec2::zero = Vec2(0, 0);

const Vec3 Vec3::unit_x = Vec3(1, 0, 0);
const Vec3 Vec3::unit_y = Vec3(0, 1, 0);
const Vec3 Vec3::unit_z = Vec3(0, 0, 1);
const Vec3 Vec3::zero = Vec3(0, 0, 0);

Vec3::Vec3() : x(0), y(0) {}
Vec3::Vec3(const Vec3 &other) : x(other.x), y(other.y), z(other.z) {}
Vec3::Vec3(const Vec2 &v) : x(v.x), y(v.y), z(0) {}

Vec3 Vec3::operator+(const Vec3 &other) const
{
    return Vec3(x + other.x, y + other.y, z + other.z);
}
Vec3 Vec3::operator-(const Vec3 &other) const
{
    return Vec3(x - other.x, y - other.y, z - other.z);
}
Vec3 Vec3::operator*(const float scalar) const
{
    return Vec3(x * scalar, y * scalar, z * scalar);
}
Vec3 Vec3::operator/(const float scalar) const
{
    return Vec3(x / scalar, y / scalar, z / scalar);
}
Vec3 Vec3::operator-() const
{
    return Vec3(-x, -y, -z);
}

Vec3 &Vec3::operator+=(const Vec3 &other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    return *this;
}
Vec3 &Vec3::operator-=(const Vec3 &other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    return *this;
}
Vec3 &Vec3::operator*=(const float scalar)
{
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}
Vec3 &Vec3::operator/=(const float scalar)
{
    this->x /= scalar;
    this->y /= scalar;
    this->z /= scalar;
    return *this;
}

bool Vec3::operator==(const Vec3 &other)
{
    return x == other.x and y == other.y and z == other.z;
}

float Vec3::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}
float Vec3::sqr_length() const
{
    return x * x + y * y + z * z;
}
float Vec3::dot(const Vec3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}
Vec3 Vec3::cross(const Vec3 &other) const
{
    return Vec3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}
void Vec3::scale_to_length(const float length)
{
    const float len = this->length();
    if (len == 0)
        throw std::invalid_argument("Cannot scale a zero-length vector");
    const float ratio = len / length;
    x *= ratio;
    y *= ratio;
    z *= ratio;
}
Vec3 Vec3::normalize() const
{
    float len = this->length();
    if (len == 0)
    {
        throw std::invalid_argument("Cannot normalize a zero-length vector");
    }
    return Vec3(x / len, y / len, z / len);
}
Vec3 &Vec3::normalize_ip()
{
    float len = this->length();
    if (len == 0)
    {
        throw std::invalid_argument("Cannot normalize a zero-length vector");
    }
    x /= len;
    y /= len;
    z /= len;
    return *this;
}

Vec3 Vec3::project(const Vec3 &normal) const
{
    float dot_product = this->dot(normal);
    float normal_length_squared = normal.sqr_length();
    if (normal_length_squared == 0)
    {
        throw std::invalid_argument("Cannot project onto a zero-length vector");
    }
    return normal * (dot_product / normal_length_squared);
}
Vec3 &Vec3::project_ip(const Vec3 &normal)
{
    float dot_product = this->dot(normal);
    float normal_length_squared = normal.sqr_length();
    if (normal_length_squared == 0)
    {
        throw std::invalid_argument("Cannot project onto a zero-length vector");
    }
    float projection_factor = dot_product / normal_length_squared;
    *this = projection_factor * normal;
    return *this;
}
Vec3 Vec3::reflect(const Vec3 &normal) const
{
    return *this - 2 * this->dot(normal) * normal;
}

Vec3 &Vec3::reflect_ip(const Vec3 &normal)
{
    *this = *this - 2 * this->dot(normal) * normal;
    return *this;
}

Vec3 Vec3::lerp(const Vec3 &other, const float w) const
{
    if (w < 0.0f || w > 1.0f)
        throw std::invalid_argument("Weight must be in range [0,1]");
    return (*this) * (1.0f - w) + w * other;
}

Vec3 Vec3::move_towards(const Vec3 &other, const float distance) const
{
    Vec3 direction = (other - *this).normalize();
    return *this + direction * distance;
}

Vec3 Vec3::move_towards_ip(const Vec3 &other, const float distance)
{
    Vec3 direction = (other - *this).normalize();
    *this = *this + direction * distance;
    return *this;
}

Vec3 operator*(const float scalar, const Vec3 &v)
{
    return Vec3(v.x * scalar, v.y * scalar, v.z * scalar);
}
// Distance to another Vec3
float Vec3::distance_to(const Vec3 &other) const
{
    return std::sqrt(distance_sqr_to(other));
}

// Squared distance to another Vec3
float Vec3::distance_sqr_to(const Vec3 &other) const
{
    float dx = x - other.x;
    float dy = y - other.y;
    float dz = z - other.z;
    return dx * dx + dy * dy + dz * dz;
}

// Clamp magnitude to a maximum length
Vec3 Vec3::clamp_magnitude(const float max_len) const
{
    float len = std::sqrt(x * x + y * y + z * z);
    if (len > max_len)
    {
        float scale = max_len / len;
        return Vec3(x * scale, y * scale, z * scale);
    }
    return *this;
}

// Clamp magnitude between min and max lengths
Vec3 Vec3::clamp_magnitude(const float min_len, const float max_len) const
{
    float len = std::sqrt(x * x + y * y + z * z);
    if (len < min_len)
    {
        float scale = min_len / len;
        return Vec3(x * scale, y * scale, z * scale);
    }
    else if (len > max_len)
    {
        float scale = max_len / len;
        return Vec3(x * scale, y * scale, z * scale);
    }
    return *this;
}

// In-place clamp magnitude to a maximum length
Vec3 &Vec3::clamp_magnitude_ip(const float max_len)
{
    float len = std::sqrt(x * x + y * y + z * z);
    if (len > max_len)
    {
        this->scale_to_length(max_len);
    }
    return *this;
}

// In-place clamp magnitude between min and max lengths
Vec3 &Vec3::clamp_magnitude_ip(const float min_len, const float max_len)
{
    float len = this->length();
    if (len < min_len)
    {
        this->scale_to_length(min_len);
    }
    else if (len > max_len)
    {
        this->scale_to_length(max_len);
    }
    return *this;
}
std::ostream &operator<<(std::ostream &out, const Vec3 &other)
{
    out << "Vec3(" << other.x << "," << other.y << "," << other.z << ")";
    return out;
}

Vec3 Vec3::rotate(const float degree, const Vec3 &axis) const
{
    float rad = degree * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    Vec3 nAxis = axis.normalize();
    Vec3 crossProduct = this->cross(nAxis);
    float dotProduct = this->dot(nAxis);

    Vec3 rotated = (*this * cosA) + (crossProduct * sinA) + (nAxis * dotProduct * (1 - cosA));

    return rotated;
}

Vec3 &Vec3::rotate_ip(const float degree, const Vec3 &axis)
{
    *this = rotate(degree, axis);
    return *this;
}

Vec3 Vec3::rotate_x(const float degree) const
{
    float rad = degree * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for X-axis
    Vec3 rotated(x,
                 cosA * y - sinA * z,
                 sinA * y + cosA * z);

    return rotated;
}

Vec3 &Vec3::rotate_x_ip(const float degree)
{
    *this = rotate_x(degree);
    return *this;
}
Vec3 Vec3::rotate_y(const float degree) const
{
    float rad = degree * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for Y-axis
    Vec3 rotated(cosA * x + sinA * z,
                 y,
                 -sinA * x + cosA * z);

    return rotated;
}

Vec3 &Vec3::rotate_y_ip(const float degree)
{
    *this = rotate_y(degree);
    return *this;
}
Vec3 Vec3::rotate_z(const float degree) const
{
    float rad = degree * (M_PI / 180.0f);
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for Z-axis
    Vec3 rotated(cosA * x - sinA * y,
                 sinA * x + cosA * y,
                 z);

    return rotated;
}

Vec3 &Vec3::rotate_z_ip(const float degree)
{
    *this = rotate_z(degree);
    return *this;
}

Vec3 Vec3::rotate_rad(const float rad, const Vec3 &axis) const
{
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    Vec3 nAxis = axis.normalize(); // Normalize the axis
    Vec3 crossProduct = this->cross(nAxis);
    float dotProduct = this->dot(nAxis);

    Vec3 rotated = (*this * cosA) + (crossProduct * sinA) + (nAxis * dotProduct * (1 - cosA));

    return rotated;
}

Vec3 &Vec3::rotate_rad_ip(const float rad, const Vec3 &axis)
{
    *this = rotate_rad(rad, axis);
    return *this;
}
Vec3 Vec3::rotate_rad_x(const float rad) const
{
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for X-axis
    Vec3 rotated(x,
                 cosA * y - sinA * z,
                 sinA * y + cosA * z);

    return rotated;
}

Vec3 &Vec3::rotate_x_rad_ip(const float rad)
{
    *this = rotate_rad_x(rad);
    return *this;
}

Vec3 Vec3::rotate_rad_y(const float rad) const
{
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for Y-axis
    Vec3 rotated(cosA * x + sinA * z,
                 y,
                 -sinA * x + cosA * z);

    return rotated;
}

Vec3 &Vec3::rotate_y_rad_ip(const float rad)
{
    *this = rotate_rad_y(rad);
    return *this;
}

Vec3 Vec3::rotate_rad_z(const float rad) const
{
    float cosA = std::cos(rad);
    float sinA = std::sin(rad);

    // Rotation matrix for Z-axis
    Vec3 rotated(cosA * x - sinA * y,
                 sinA * x + cosA * y,
                 z);

    return rotated;
}

Vec3 &Vec3::rotate_z_rad_ip(const float rad)
{
    *this = rotate_rad_z(rad);
    return *this;
}

float Vec3::angle_to(const Vec3 &v) const
{
    float dotProduct = this->dot(v);
    float magnitudeA = this->length();
    float magnitudeB = v.length();

    if (magnitudeA == 0 || magnitudeB == 0)
    {
        throw std::invalid_argument("Cannot compute angle with zero-length vector");
    }

    float cosAngle = dotProduct / (magnitudeA * magnitudeB);

    cosAngle = clamp(cosAngle, -1.0f, 1.0f);

    float angleRad = std::acos(cosAngle);

    float angleDeg = angleRad * (180.0f / static_cast<float>(M_PI));

    return angleDeg;
}

VertexArray::VertexArray()
{
    vertices = nullptr;
    size = 0;
};

VertexArray::Iterator VertexArray::begin()
{
    return VertexArray::Iterator(*this);
}
VertexArray::Iterator VertexArray::end()
{
    return VertexArray::Iterator(*this)+this->size;
}

VertexArray::Iterator VertexArray::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++current;
    return temp;
}
VertexArray::Iterator &VertexArray::Iterator::operator++()
{
    ++current;
    return *this;
}

VertexArray::Iterator VertexArray::Iterator::operator+(int x) const
{
    Iterator temp = *this;
    temp.advance(x);
    return temp;
}

void VertexArray::Iterator::advance(int n)
{
    current += n;
}

VertexArray::Iterator::Iterator(VertexArray &va) : current(va.vertices) {}
Vec2 &VertexArray::Iterator::operator*() const { return *current; }
Vec2 *VertexArray::Iterator::operator->() const { return current; }

bool VertexArray::Iterator::operator==(const Iterator &other) const
{
    return current == other.current;
}
bool VertexArray::Iterator::operator!=(const Iterator &other) const
{
    return current != other.current;
}