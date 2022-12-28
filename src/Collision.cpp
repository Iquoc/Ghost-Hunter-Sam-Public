#include "Collision.h"
#include "ECS\ColliderComponent.h"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB)
{
	if (rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y)
	{
		return true;
	}
	
	return false;
}

bool Collision::AABB(const ColliderComponent& collA, const ColliderComponent& collB)
{
	if (AABB(collA.collider, collB.collider))
	{
		std::cout << collA.tag << " hit " << collB.tag << std::endl;
		return true;
	}

	return false;
}