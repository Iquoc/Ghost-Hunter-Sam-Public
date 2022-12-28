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
	int speed = 3;

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
};