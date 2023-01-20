#include "Main.h"
#include "Game.h"
#include <SDL.h>
#include <cstdio>
#include <stdio.h>
#include <iostream>
using namespace std;

Game* game = nullptr;

int counter;

int main(int argc, char* args[]) {
	
	//int age;
	//cout << "Enter your age: ";
	//cin >> age;

	//cout << "You are " << age << " years old?!";

	//int numberGrid[3][2] = {
	//	{1, 2},
	//	{3, 4},
	//	{5, 6}
	//};

	//for (int i = 0; i < 3; i++) {
	//	for (int j = 0; j < 2; j++) {
	//		cout << numberGrid[i][j];
	//	}
	//	cout << endl;
	//}

	const int FPS = 60; // frames per second
	const int frameDelay = 1000 / FPS; // 16.667 seconds per frame; time in milliseconds

	Uint32 frameStart;	// get number of milliseconds since SDL lib was initialized
	int frameTime;	// number of time to execute a frame

	game = new Game();
	game->init("Ghost Hunter Sam", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);	// match 32 bit resolution
	// 25 x 20; 5:4

	std::srand(std::time(0));	// gives the random function a new seed, using the time in seconds since the UNIX epoch

	while (game->running()) {
		
		frameStart = SDL_GetTicks();	

		game->handleEvents();	// access members of the structure using pointers
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	
	SDL_Init(SDL_INIT_EVERYTHING);
	//cout << "Hello World! ";
	//printf("Dum Dum ");
	return 0;
}