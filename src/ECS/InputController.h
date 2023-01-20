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
	Vector2D path;
	bool isMoving;

	bool doPathing;

	int distance;

	int xMouse, yMouse, counter;

	Uint32 inputType, bufferType;
	SDL_Keycode input, buffer; // allows for smoother input control by storing user input for proceeding events
	Uint32 frameRun;

	bool closetTime, inCloset;

	bool temp;	// temporary bool value

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		movePoint = new TransformComponent;
		movePoint->position = transform->position;
	/*	movePoint = (transform->position.y / 32 - 1) * 10 + transform->position.x;*/

		distance = 32 * transform->getScale() * 3 / 4;

		counter = 0;

		closetTime = false;
		doPathing = false;

		temp = true;
	}

	void update() override
	{
		if (buffer == NULL) {
			inputType = Game::event.type;
			input = Game::event.key.keysym.sym;
			//std::cout << "Not buffered" << std::endl;
		}
		else {
			inputType = bufferType;
			input = buffer;
			std::cout << "Buffered" << std::endl;
		}

		/*counter++;
		if (counter % 120 == 0) {
			SDL_GetMouseState(&xMouse, &yMouse);
			std::cout << xMouse << "," << yMouse << std::endl;

			counter = 0;
		}*/

		// transform->position == movePoint->position
		if (transform->position == movePoint->position) {
			isMoving = false;
			doPathing = false;
			//std::cout << "not moving" << std::endl;
		}
		else {
			isMoving = true;
			
			//if (transform->position.distance(movePoint->position) <= transform->speed + 1) {
			//	if (Game::event.type == SDL_KEYDOWN) {
			//		if (input == SDLK_w || input == SDLK_a || input == SDLK_s || input == SDLK_d) {
			//			bufferType = SDL_KEYDOWN;
			//			buffer = Game::event.key.keysym.sym;
			//			std::cout << "Buffer Input" << std::endl;
			//		}
			//	}
			//}
		}

		if (inCloset) {
			bufferType = NULL;
			buffer = NULL;
		}

		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_Q]) {
			std::cout << "Q" << std::endl;
		}

		if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_A] || state[SDL_SCANCODE_S] || state[SDL_SCANCODE_D]) {
			counter++;
			if (counter % 60 == 0) {
				transform->speed = 5;
				counter = 0;
				//std::cout << "RUNNING" << std::endl;
			}
		}
		else {
			counter = 0;
			transform->speed = 3;
		}

		if (!isMoving && !inCloset)
		{
			//std::cout << "in position" << std::endl;
			movePoint->prevPos = transform->position;
			sprite->play("Idle");
			//std::cout << "can move" << std::endl;
			
			if (inputType == SDL_KEYDOWN)
			{
				bufferType = NULL;
				buffer = NULL;

				switch (input) {
				case SDLK_w:	// w key down; UP
					//movePoint->position -= Vector2D(0, distance);
					move(Vector2D(0, -distance));
					break;
				case SDLK_a:	// a key down; LEFT
					move(Vector2D(-distance, 0));
					sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
					break;
				case SDLK_s:	// s key down; DOWN
					move(Vector2D(0, distance));
					break;
				case SDLK_d:	// d key down; RIGHT
					move(Vector2D(distance, 0));
					sprite->spriteFlip = SDL_FLIP_NONE;
					break;
				default:
					break;
				}
			}

			//std::cout << "Move Point Position: " << movePoint->position.x << "," << movePoint->position.y << std::endl;
		}
		else {
			//abs(transform->position.x - movePoint->position.x) < transform->speed&& abs(transform->position.y - movePoint->position.y) < transform->speed)
			if (transform->position.distance(transform->position, movePoint->position) <= transform->speed * 2)
			{
				transform->position = movePoint->position;

				if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_A] || state[SDL_SCANCODE_S] || state[SDL_SCANCODE_D]) {
					bufferType = SDL_KEYDOWN;
					std::cout << "Buffer Input" << std::endl;
				}

				if (state[SDL_SCANCODE_W]) {
					buffer = SDLK_w;
				}

				if (state[SDL_SCANCODE_A]) {
					buffer = SDLK_a;
				}

				if (state[SDL_SCANCODE_S]) {
					buffer = SDLK_s;
				}

				if (state[SDL_SCANCODE_D]) {
					buffer = SDLK_d;
				}
			}
			else
			{
				move(Vector2D(0, 0));
			}
			//std::cout << transform->moveToward(movePoint->position) << std::endl;
		}


		if (inputType == SDL_KEYUP)
		{
			switch (input) {
			//case SDLK_w:	// w key down
			//	transform->velocity.y = 0;
			//	//sprite->play("Idle");
			//	break;
			//case SDLK_a:
			//	transform->velocity.x = 0;
			//	//sprite->play("Idle");
			//	break;
			//case SDLK_s:
			//	transform->velocity.y = 0;
			//	//sprite->play("Idle");
			//	break;
			//case SDLK_d:
			//	transform->velocity.x = 0;
			//	//sprite->play("Idle");
			//	break;
			case SDLK_e:
				if (closetTime && !doPathing) {
					if (inCloset) {
						//movePoint->position = transform->prevPos;
						reset();
						std::cout << "IT'S not CLOSET TIME!!! " << inCloset << std::endl;
						std::cout << transform->prevPos.x << "," << transform->prevPos.y << std::endl;
						inCloset = false;
					}
					else
					{
						std::cout << "IT'S CLOSET TIME!!!" << std::endl;
						doPathing = true;
						pathing(path);
					}
				}
				else {
					std::cout << "nope..." << std::endl;
				}
				break;
			case SDLK_ESCAPE:
				Game::isRunning = false;
				break;
			default:

				break;
			}
		}

		inputType = NULL;
		input = NULL;
	}

	void reset() {
		movePoint->position = movePoint->getPreviousPosition();
	}

	void closetTimeSwitch() {
		closetTime = !closetTime;
	}

	void pathing(Vector2D pointB) {
		if (doPathing) {
			movePoint->prevPos = movePoint->position;
			movePoint->position = pointB;
		}
	}

	void move(Vector2D direction) {
		movePoint->position += direction;
		transform->position += transform->moveToward(movePoint->position) * transform->speed;
		sprite->play("Walk");
	}
};