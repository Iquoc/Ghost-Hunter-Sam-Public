#pragma once
#include "Components.h"
#include "../Vector2D.h"

// struct; everything by default is public
// class; everything by default is private
class TransformComponent : public Component
{
public:

	Vector2D position;
	Vector2D velocity;
	int speed = 1;

	Vector2D prevPos;

	int height = 16;
	int width = 16;
	int scale = 1;

	TransformComponent()		// default constructor
	{
		position.zero();
	}
	
	// Static Camera
	//TransformComponent(int sc)
	//{
	//	position.zero();
	//	scale = sc;
	//}

	// Camera Follows Player
	TransformComponent(int sc)
	{
		position.x = 300;
		position.y = 300;
		scale = sc;
	}

	TransformComponent(float x, float y, int sc)
	{
		position.x = x;
		position.y = y;
		scale = sc;
	}

	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override
	{
		velocity.zero();
	}

	// Update A; Static Camera
	/*void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}*/
	
	// Update B; Camera Follows Player
	void update() override
	{
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	int getScale()
	{
		return scale;
	}

	Vector2D getCenter() 
	{
		int cX, cY;
		cX = position.x + (width) / 2;
		cY = position.y + (width) / 2;
		Vector2D center = Vector2D(cX, cY);
		return center;
	}

	Vector2D getPreviousPosition()
	{
		return prevPos;
	}

	Vector2D moveToward(Vector2D destPos)
	{
		Vector2D direction = destPos - position;
		/*return direction.binary() * Vector2D(speed, speed);*/
		return direction.binary();
	}
};