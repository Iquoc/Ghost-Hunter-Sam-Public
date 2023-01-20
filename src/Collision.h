#pragma once
#include <SDL.h>
#include "ECS/ColliderComponent.h"

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);		// using Axis Aligned Bounding Box (AABB) collision detection
	
	static bool AABB(const ColliderComponent& collA, const ColliderComponent& collB);

	static bool AABB(Circle circleA, Circle circleB);

	static bool AABB(const SDL_Rect& rectA, Circle circleB);
};