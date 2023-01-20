#include "Collision.h"
#include <algorithm>
//#include "ECS\ColliderComponent.h"

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

bool Collision::AABB(Circle circleA, Circle circleB)
{
	int x1, x2, y1, y2, r1, r2;
	x1 = circleA.x;
	x2 = circleB.x;
	y1 = circleA.y;
	y2 = circleB.y;

	r1 = circleA.r;
	r2 = circleB.r;

	int dx, dy, rs;
	dx = x1 - x2;
	dy = y1 - y2;
	rs = r1 + r2;

	if ((dx * dx) + (dy * dy) <= rs * rs) {
		return true;
	}
	return false;
	
	//
	//// dx is the 
	//int dx, dy, rs;
	//dx = circleA.x - circleA.r + circleA.x - (circleB.x * 2 - circleB.r);
	//dy = circleA.y * 2 - circleA.r - (circleB.y * 2 - circleB.r);
	//rs = circleA.r + circleB.r;
	//dx *= dx;
	//dy *= dy;
	//rs *= rs;
	//if (dx + dy < rs)
	//{
	//	return true;
	//}
	//return false;
}

// std::clamp()
// clamping
// min (12, n) = 12 to n
// max (35, n) = n to 35
// max(35, min(12, n)) = 12 to 35
bool Collision::AABB(const SDL_Rect& rectA, Circle circleB)
{
	int x1, x2, y1, y2, r1, r2;
	x1 = rectA.x;
	x2 = circleB.x;
	y1 = rectA.y;
	y2 = circleB.y;
	r1 = rectA.w;
	r2 = circleB.r;

	// nearest point to the circle
	int xClamp = std::max(x1, std::min(x1 + r1, x2));
	int yClamp = std::max(y1, std::min(y1 + r1, y2));

	int dx, dy, rs;
	dx = (xClamp - x2);
	dy = (yClamp - y2);
	rs = r2 * r2;

	// pythagorean theorem to compare the distance from the center of the circle to the distance to the nearest point of the rectangle
	if ((dx * dx) + (dy * dy) <= rs) {
		return true;
	}
	return false;
}