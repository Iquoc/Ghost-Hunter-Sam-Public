#pragma once
#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"	// ../ path back a directory
#include "Animation.h"
#include <map>
#include "AssetManager.h"


class SpriteComponent : public Component
{
private:
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	bool animated = false;
	int frames = 0;
	int speed = 100;

public:

	int animIndex = 0;

	std::map<const char*, Animation> animations;

	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;
	SpriteComponent(std::string id)
	{
		setTexture(id);
	}

	SpriteComponent(std::string id, bool isAnimated)
	{
		animated = isAnimated;

		Animation idle = Animation(0, 4, 500);
		Animation walk = Animation(1, 4, 100);

		animations.emplace("Idle", idle);
		animations.emplace("Walk", walk);

		play("Idle");
		setTexture(id);
	}

	~SpriteComponent()
	{

	}

	void setTexture(std::string id) {
		texture = Game::assets->getTexture(id);
	}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->height;
		srcRect.h = transform->height;

	}
	
	// Update A; Static Camera
	//void update() override
	//{
	//	if (animated) {
	//		srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
	//	}

	//	srcRect.y = animIndex * transform->height;

	//	destRect.x = static_cast<int>(transform->position.x);
	//	destRect.y = static_cast<int>(transform->position.y);
	//
	//	destRect.w = transform->width * transform->scale;
	//	destRect.h = transform->height * transform->scale;
	//}

	// Update B; Camera Follows Player
	void update() override
	{
		if (animated) {
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
		}

		srcRect.y = animIndex * transform->height;

		destRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
		destRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
	
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void draw() override
	{
		TextureManager::draw(texture, srcRect, destRect, spriteFlip);
	}

	void play(const char* animName)
	{
		frames = animations[animName].frames;
		speed = animations[animName].speed;
		animIndex = animations[animName].index;
	}
};