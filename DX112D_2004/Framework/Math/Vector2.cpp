#include "Framework.h"

Vector2::Vector2() : Float2(0, 0)
{    
}

Vector2::Vector2(float x, float y) : Float2(x, y)
{
}

Vector2::Vector2(Float2 value) : Float2(value)
{
}

Vector2 Vector2::operator+(const Vector2& value) const
{
    return Vector2(x + value.x, y + value.y);
}

Vector2 Vector2::operator-(const Vector2& value) const
{
    return Vector2(x - value.x, y - value.y);
}

Vector2 Vector2::operator*(const Vector2& value) const
{
    return Vector2(x * value.x, y * value.y);
}

Vector2 Vector2::operator/(const Vector2& value) const
{
    return Vector2(x / value.x, y / value.y);
}

Vector2 Vector2::operator*(const float& value) const
{
    return Vector2(x * value, y * value);
}

void Vector2::operator+=(const Vector2& value)
{
    x += value.x;
    y += value.y;
}

void Vector2::operator-=(const Vector2& value)
{
    x -= value.x;
    y -= value.y;
}

void Vector2::operator*=(const Vector2& value)
{
    x *= value.x;
    y *= value.y;
}

void Vector2::operator/=(const Vector2& value)
{
    x /= value.x;
    y /= value.y;
}

void Vector2::operator+=(const float& value)
{
    x += value;
    y += value;
}

void Vector2::operator-=(const float& value)
{
    x -= value;
    y -= value;
}

void Vector2::operator*=(const float& value)
{
    x *= value;
    y *= value;
}

void Vector2::operator/=(const float& value)
{
    x /= value;
    y /= value;
}

bool Vector2::operator==(const Vector2& value) const
{
    if(x == value.x && y == value.y)
        return true;

    return false;
}

float Vector2::Length() const
{
    return sqrt(LengthSqr());
}

float Vector2::LengthSqr() const
{
    return x*x + y*y;
}

void Vector2::Normalize()
{
    float length = Length();

    x /= length;
    y /= length;
}

Vector2 Vector2::Normal() const
{
    float length = Length();

    return Vector2(x / length, y / length);
}

float Vector2::Angle() const
{
    return atan2(y, x);
}

float Vector2::Dot(const Vector2 value) const
{
    return x * value.x + y * value.y;
}

float Vector2::Cross(const Vector2 value) const
{
    return x * value.y - y * value.x;
}

float Vector2::Distance(const Vector2& v1, const Vector2& v2)
{
    return (v2 - v1).Length();
}

Vector2 Vector2::TransformCoord(const Vector2& v, const Matrix& mat)
{
    XMVECTOR temp = XMLoadFloat2(&v);

    temp = XMVector2TransformCoord(temp, mat);

    Vector2 result;
    XMStoreFloat2(&result, temp);

    return result;
}

Vector2 operator*(const float f, const Vector2& v)
{
    return v * f;
}
