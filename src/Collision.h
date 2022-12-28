#pragma once
#include <SDL.h>

class ColliderComponent;

class Collision
{
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);		// using Axis Aligned Bounding Box (AABB) collision detection
	
	static bool AABB(const ColliderComponent& collA, const ColliderComponent& collB);
};