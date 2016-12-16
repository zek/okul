#ifndef _VECTOR2D
#define _VECTOR2D

#include "math.h"

class Vector2D
{
public:

	float   x;
	float   y;

	Vector2D() 
	{
		x=0.0f;
		y=0.0f;
	}

	// use r for x, s for y 
	Vector2D(float r, float s)
	{
		x = r;
		y = s;
	}

	// use r for x, s for y 
	Vector2D& Set(float r, float s);
	
	// adds v to *this and returns reference to *this
	Vector2D& operator +=(const Vector2D& v);
	
	// subtracts v to *this and returns reference to *this
	Vector2D& operator -=(const Vector2D& v);
	
	// multiplies *this with scalar t and returns reference to *this
	Vector2D& operator *=(float t);
	
	// divides *this with scalar t and returns reference to *this
	Vector2D& operator /=(float t);
		
	// returns a negated form of *this as a new vector 
	Vector2D operator -(void) const;
	
	// returns sum of *this and v as a new vector
	Vector2D operator +(const Vector2D& v) const;
	
	// returns the difference between *this and v as a new vector
	Vector2D operator -(const Vector2D& v) const;
	
	// returns the multiplication of *this and t as a new vector
	Vector2D operator *(float t) const;
	
	// returns the division of *this and t as a new vector
	Vector2D operator /(float t) const;
	
	// returns true if *this is equal to v
	bool operator ==(const Vector2D& v) const;
	
	// returns true if *this is not equal to v
	bool operator !=(const Vector2D& v) const;
	
	// normalizes *this and returns a reference
	Vector2D& Normalize(void)
	{
		float srt = sqrtf(x * x + y * y);
		x /= srt;
		y /= srt;
		return *this;
	}

};

inline Vector2D operator *(float t, const Vector2D& v)
{
	return (Vector2D(t * v.x, t * v.y));
}
#endif