#ifndef _RACKET
#define _RACKET

#include "Vector2D.h"
#include "Ball.h"

class Racket
{
public:

	float size;
	Vector2D position;

public:
	Racket()
		:size(1)
		,position(0,0)
	{
	}

	// sets size
	void setSize(unsigned int s);

	// sets position
	void setPosition(const Vector2D& pos);

	// returns size
	unsigned int getSize();
	
	// returns position
	Vector2D getPosition();
	
};

#endif






