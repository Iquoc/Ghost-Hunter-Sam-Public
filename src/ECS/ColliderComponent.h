#pragma once
#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect collider;	// collider box
	std::string tag;	// identifier for object collision

	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	ColliderComponent()
	{
		
	}

	ColliderComponent(std::string objectTag) {
		tag = objectTag;
	}

	ColliderComponent(std::string objectTag, int xPos, int yPos, int size) {
		tag = objectTag;
		collider.x = xPos;
		collider.y = yPos;
		collider.h = collider.w = size;
	}

	void init() override
	{
		if (!entity->hasComponent<TransformComponent>())	// makes sure the entity has a transform component
		{
			entity->addComponent<TransformComponent>();		// if not, add transform component
		}
		transform = &entity->getComponent<TransformComponent>();

		texture = TextureManager::loadTexture("assets/texture/collision_texture.png");
		srcRect = { 0, 0, 32, 32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };

		/*Game::colliders.push_back(this);*/
	}

	void update() override
	{
		if (tag != "terrain")
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);

			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}
	
		destRect.x = collider.x - Game::camera.x;
		destRect.y = collider.y - Game::camera.y;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}
};