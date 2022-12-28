#pragma once
#include "ECS.h"
#include "../Game.h"
#include "../TextureManager.h"
#include "../Vector2D.h"

class TileComponent : public Component
{
public:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	Vector2D position;

	int sc = 4;

	TileComponent() = default;

	~TileComponent() {
		SDL_DestroyTexture(texture);
	}

	TileComponent(int srcX, int srcY, int xPos, int yPos, int tSize, int tScale, std::string id)
	{
		texture = Game::assets->getTexture(id);
		position.x = xPos;
		position.y = yPos;

		sc = tScale;

		srcRect.x = srcX;
		srcRect.y = srcY;
		srcRect.w = srcRect.h = tSize;

		destRect.x = xPos;
		destRect.y = yPos;
		destRect.w = destRect.h = tSize * sc;
	}

	// Update A; Static Camera
	void update() override
	{
		destRect.x = position.x - Game::camera.x;
		destRect.y = position.y - Game::camera.y;
	}

	//void update() override
	//{
	//	destRect.x = position.x - Game::camera.x;
	//	destRect.y = position.y - Game::camera.y;
	//}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
	}

	//void init() override
	//{
	//	entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 2);
	//	transform = &entity->getComponent<TransformComponent>();

	//	entity->addComponent<SpriteComponent>(filePath);
	//	sprite = &entity->getComponent<SpriteComponent>();
	//}
};