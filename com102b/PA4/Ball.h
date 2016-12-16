#ifndef _BALL
#define _BALL

#include "Vector2D.h"
#include <iostream>


class Ball
{
private:
	Vector2D position;
	Vector2D direction;
	float velocity;
	float radius;
	float color_r;
	float color_g;
	float color_b;
public:

	Ball(float a=0, float b=0)
	{
		position = Vector2D(a,b);
		direction = Vector2D(1,1);

		velocity = 0.3f;
		radius = 5.0f;
		color_r = 1.0f;
		color_g = 0.0f;
		color_b = 0.0f;
	}

	// sets position
	void setPosition(const Vector2D& pos);

	// sets normalized direction
	void setDirection(Vector2D& dir);

	// sets velocity
	void setVelocity(float vel);

	// sets radious
	void setRadious(float rad);

	// sets color components: R for color_r, G for color_g, B for color_b
	void setColor(float R, float G, float B);

	// returns position
	Vector2D getPosition();

	// returns direction
	Vector2D getDirection();

	// returns velocity
	float getVelocity();

	// returns radious
	float getRadious();

	// returns R,G,B color components of the ball
	float getRed();
	float getGreen();
	float getBlue();

	// updates and returns the position of the ball using the formula:
	// pos = pos + velocity*normalized_direction;
	Vector2D updatePosition();


};

#endif
