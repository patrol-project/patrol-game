#pragma once

#include<math.h>

class Vector2D
{
public:
	Vector2D(float x, float y) : xpos(x), ypos(y) {}
	float getX() { return xpos; }
	float getY() { return ypos; }
	void setX(float x) { xpos = x; }
	void setY(float y) { ypos = y; }
	float length() { return sqrt(xpos * xpos + ypos * ypos); }

	Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(xpos + v2.xpos, ypos + v2.ypos);
	}

	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	{
		v1.xpos += v2.xpos;
		v1.ypos += v2.ypos;
		return v1;
	}
	Vector2D operator*(float scalar)
	{
		return Vector2D(xpos * scalar, ypos * scalar);
	}
	Vector2D& operator*=(float scalar)
	{
		xpos *= scalar;
		ypos *= scalar;
		return *this;
	}
	Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(xpos - v2.xpos, ypos - v2.ypos);
	}
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	{
		v1.xpos -= v2.xpos;
		v1.ypos -= v2.ypos;
		return v1;
	}
	Vector2D operator/(float scalar)
	{
		return Vector2D(xpos / scalar, ypos / scalar);
	}
	Vector2D& operator/=(float scalar)
	{
		xpos /= scalar;
		ypos /= scalar;
		return *this;
	}
	void normalize()
	{
		float l = length();
		if (l > 0) // we never want to attempt to divide by 0
		{
			(*this) *= 1 / l;
		}
	}
private:
	float xpos;
	float ypos;
};
