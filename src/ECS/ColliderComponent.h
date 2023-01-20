#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

struct Circle {
public:
	int x, y, r, sc;
};

class ColliderComponent : public Component
{
private:
	bool drawColliders = true;

public:
	SDL_Rect collider;	// collider box
	std::string tag;	// identifier for object collision

	Circle circle;	// collider circle
	Circle getCircle() {
		return circle;
	}
	void setCircle(int x, int y, float r)
	{
		circle.x = x;
		circle.y = y;
		circle.r = r;
	}
	void printCircle() {
		std::cout << circle.x << "," << circle.y << "," << circle.r << std::endl;
		std::cout << destRect.x << ";" << destRect.y << ";" << destRect.w << std::endl;
	}
	bool getCollision(int* other) {
		//int dx, dy, rs;
		//dx = position.x + circle.x - (other.x + other.getCenter.x);
		//dy = position.y + circle.y - (other.y + other.getCenter.y);
		//rs = circle.r + other.r;
		//dx *= dx;
		//dy *= dy;
		//rs *= rs;
		//if (dx + dy < rs)
		//{
		//	return true;
		//}
		//return false;
	}

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool isCircle;

	TransformComponent* transform;

	ColliderComponent() {
		isCircle = false;
	}
	ColliderComponent(std::string objectTag, bool isC) {
		tag = objectTag;
		isCircle = isC;
	}

	// size is width/height or diameter
	ColliderComponent(std::string objectTag, int xPos, int yPos, float size, bool isC) {
		isCircle = isC;
		tag = objectTag;

		if (isCircle) {
			setCircle(xPos, yPos, size / 2);
		}
		else {
			collider.x = xPos;
			collider.y = yPos;
			collider.h = collider.w = size;
		}
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())	// makes sure the entity has a transform component
		{
			entity->addComponent<TransformComponent>();		// if not, add transform component
		}
		transform = &entity->getComponent<TransformComponent>();

		srcRect = { 0, 0, 32, 32 };

		if (isCircle) {
			texture = TextureManager::loadTexture("assets/texture/collision_texture_circle.png");	
			
			/*std::cout << circle.r << std::endl;*/
			float radius;
			if (circle.r == 0) {
				radius = (transform->scale * transform->width) / 2;

				//std::cout << circle.r << std::endl;
			}
			else {
				radius = circle.r * ((transform->scale * transform->width) / 2);
				//std::cout << circle.r << std::endl;
			}
			int x = static_cast<int>(transform->position.x) + radius;
			int y = static_cast<int>(transform->position.y) + radius;
			setCircle(x, y, radius);
			
			int r = static_cast<int>(radius);

			destRect.x = circle.x - r;
			destRect.y = circle.y - r;
			destRect.w = destRect.h = radius * 2;
		}
		else {
			texture = TextureManager::loadTexture("assets/texture/collision_texture.png");
			destRect = { collider.x, collider.y, collider.w, collider.h };
		}
		
		/*Game::colliders.push_back(this);*/
	}

	void update() override
	{

		if (isCircle) {
			int centerDist = (transform->scale * transform->width) / 2;
			circle.x = static_cast<int>(transform->position.x) + centerDist;
			circle.y = static_cast<int>(transform->position.y) + centerDist;

			destRect.x = circle.x - circle.r - Game::camera.x;
			destRect.y = circle.y - circle.r - Game::camera.y;
			destRect.w = destRect.h = circle.r * 2;

			/*printCircle();*/
		}
		else {
			if (tag != "terrain")
			{
				collider.x = static_cast<int>(transform->position.x);
				collider.y = static_cast<int>(transform->position.y);

				collider.w = transform->width * transform->scale;
				collider.h = transform->height * transform->scale;
			}

			// subtracting by the camera x,y aligns the render SDL_Rect with the position of the object
			destRect = { collider.x - Game::camera.x , collider.y - Game::camera.y, collider.w, collider.h };
		}
	}

	void draw() override
	{
		if (drawColliders) {
			TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
		}
	}
};