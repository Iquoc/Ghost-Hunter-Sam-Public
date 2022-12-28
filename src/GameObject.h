#pragma once
#include "Game.h"


class GameObject {

public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();	// clears memory of object

	void update();
	void render();

private:

	int xPos;
	int yPos;

	SDL_Texture* objTex;
	SDL_Rect srcRect, destRect;
	SDL_Renderer* renderer;

};