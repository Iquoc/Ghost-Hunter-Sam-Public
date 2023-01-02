#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class InputController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	TransformComponent* movePoint;

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		movePoint = new TransformComponent;
		movePoint->position = transform->position;
	/*	movePoint = (transform->position.y / 32 - 1) * 10 + transform->position.x;*/
	}

	void update() override
	{
		//if (Game::event.type == SDL_KEYDOWN)
		//{
		//	switch (Game::event.key.keysym.sym) {
		//	case SDLK_w:	// w key down
		//		transform->velocity.y = -1;
		//		sprite->play("Walk");
		//		break;
		//	case SDLK_a:
		//		transform->velocity.x = -1;
		//		sprite->play("Walk");
		//		sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
		//		break;
		//	case SDLK_s:
		//		transform->velocity.y = 1;
		//		sprite->play("Walk");
		//		break;
		//	case SDLK_d:
		//		transform->velocity.x = 1;
		//		sprite->play("Walk");
		//		sprite->spriteFlip = SDL_FLIP_NONE;
		//		break;
		//	default:
		//		break;
		//	}
		//}

		if (transform->position == movePoint->position)
		{
			movePoint->prevPos = transform->position;
			sprite->play("Idle");
			if (Game::event.type == SDL_KEYDOWN)
			{
				int distance = 32 * transform->getScale() * 3 / 4;
				switch (Game::event.key.keysym.sym) {
				case SDLK_w:	// w key down; UP
					movePoint->position -= Vector2D(0, distance);
					break;
				case SDLK_a:	// a key down; LEFT
					movePoint->position -= Vector2D(distance, 0);
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_s:	// s key down; DOWN
					movePoint->position += Vector2D(0, distance);
					break;
				case SDLK_d:	// d key down; RIGHT
					movePoint->position += Vector2D(distance, 0);
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				default:
					break;
				}
			}
			//std::cout << "Move Point Position: " << movePoint->position.x << "," << movePoint->position.y << std::endl;
		}
		else
		{
			//transform->position += Vector2D(0, 5);
			if (abs(transform->position.x - movePoint->position.x) < transform->speed && abs(transform->position.y - movePoint->position.y) < transform->speed)
			{
				transform->position = movePoint->position;
			}
			else
			{
				transform->position += transform->moveToward(movePoint->position);
				sprite->play("Walk");
			}
			//std::cout << transform->moveToward(movePoint->position) << std::endl;
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:	// w key down
				transform->velocity.y = 0;
				//sprite->play("Idle");
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				//sprite->play("Idle");
				break;
			case SDLK_s:
				transform->velocity.y = 0;
				//sprite->play("Idle");
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				//sprite->play("Idle");
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:

				break;
			}
		}
	}

	void reset() {
		movePoint->position = movePoint->getPreviousPosition();
	}
};