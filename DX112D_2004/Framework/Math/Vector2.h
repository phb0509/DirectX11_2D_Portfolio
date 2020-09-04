#pragma once

class Vector2 : public Float2
{
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Float2 value);

	Vector2 operator+ (const Vector2& value) const;
	Vector2 operator- (const Vector2& value) const;
	Vector2 operator* (const Vector2& value) const;
	Vector2 operator/ (const Vector2& value) const;

	Vector2 operator* (const float& value) const;
	friend Vector2 operator* (const float f, const Vector2& v);

	void operator+= (const Vector2& value);
	void operator-= (const Vector2& value);
	void operator*= (const Vector2& value);
	void operator/= (const Vector2& value);
	void operator+= (const float& value);
	void operator-= (const float& value);
	void operator*= (const float& value);
	void operator/= (const float& value);

	bool operator== (const Vector2& value) const;

	float Length() const;
	float LengthSqr() const;

	void Normalize();
	Vector2 Normal() const;

	float Angle() const;

	float Dot(const Vector2 value) const;
	float Cross(const Vector2 value) const;

	static float Distance(const Vector2& v1, const Vector2& v2);
	static Vector2 TransformCoord(const Vector2& v, const Matrix& mat);
};