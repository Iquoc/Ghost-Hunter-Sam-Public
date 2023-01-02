#pragma once
#include "Components.h"

class AIController : public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;

	TransformComponent* movePoint;
	int distance;

	int action;
	int avoidCase;		// temp AI

	int counter;

	AIController(){}
	AIController(std::string id, int level)
	{

	}
	~AIController()
	{}

	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();


		movePoint = new TransformComponent();
		movePoint->position = transform->position;

		distance = 32 * transform->getScale() * 3 / 4;
		
		counter = 0;
	}
	
	void update() override
	{
		counter++;

		int beg = 0;
		int end = 4;

		if (transform->position == movePoint->position) {
			if (counter % 6 == 0) {
				action = std::rand() % ((end - beg) + 1) + beg;

				while (action == avoidCase) {
					action = std::rand() % ((end - beg) + 1) + beg;
				}

				movePoint->prevPos = transform->position;
				switch (action) {
				case 0:		// absolutely nothing...
					break;
				case 1:		// UP
					movePoint->position -= Vector2D(0, distance);
					avoidCase = NULL;
					break;
				case 2:		// LEFT
					movePoint->position -= Vector2D(distance, 0);
					avoidCase = NULL;
					break;
				case 3:		// DOWN
					movePoint->position += Vector2D(0, distance);
					avoidCase = NULL;
					break;
				case 4:		// RIGHT
					movePoint->position += Vector2D(distance, 0);
					avoidCase = NULL;
					break;
				default:
					break;
				}
				//std::cout << "Move Point Position: " << movePoint->position.x << "," << movePoint->position.y << std::endl;
				counter = 0;
			}
		}
		else
		{
			if (abs(transform->position.x - movePoint->position.x) < transform->speed && abs(transform->position.y - movePoint->position.y) < transform->speed)
			{
				transform->position = movePoint->position;
			}
			else
			{
				transform->position += transform->moveToward(movePoint->position);

			}
		}
	}

	void reset() {
		avoidCase = action;		// temp AI
		movePoint->position = movePoint->getPreviousPosition();
	}
};


