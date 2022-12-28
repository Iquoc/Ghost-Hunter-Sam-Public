#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <vector>

class AssetManager;		// forward declaration fixed error, "missing type specifier"
class ColliderComponent;

class Game {

public:
	Game();
	~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean(); // clean memory

	bool running() { return isRunning; };

	static SDL_Event event;
	static SDL_Renderer* renderer;

	static bool isRunning;

	static SDL_Rect camera;

	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupEnemies,
		groupColliders,
		groupProjectiles
	};

private:
	int counter = 0;
	SDL_Window* window;

};
