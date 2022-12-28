#include "Game.h"
#include "TextureManager.h"
#include "Map.h"
#include "ECS/Components.h"
#include "Vector2D.h"
#include "Collision.h"
#include "AssetManager.h"
#include <sstream>

Map* map;

SDL_Texture* playerTex;

SDL_Rect srcR, destR;

int scale;

SDL_Renderer* Game::renderer = nullptr;

bool Game::isRunning = false;

SDL_Event Game::event;	// intializes object of SDL_Event
Manager manager;
AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect Game::camera = { 0,0,800, 640 };

// AI
auto& player(manager.addEntity());
auto& enemy(manager.addEntity());

// UI
auto& label(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}

// class :(scope resolution): method
// :: used to define method outside of the class

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{
	int flags = 0;	// flags SDL_Window

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;	// sets the window to fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)		// includes all subsystems
	{
		std::cout << "Subsystems Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);		// creates window
		if (window)		// checks if window is created
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);	// creates renderer, -1 creates renderer with the first supporting flag
		if (renderer)	// checks if renderer is created
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);	// draws renderer according to rgb and alpha number
			std::cout << "Renderer created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false; // the game did not setup initial functions
	}

	if (TTF_Init() == -1) {
		std::cout << "Error : SDL_TTF" << std::endl;
	}

	// Assets Implementation
	assets->addTexture("terrain", "assets/texture/default_texture3.png");
	assets->addTexture("player", "assets/player/sam_anim (2).png");
	assets->addTexture("enemy", "assets/enemy/ghost.png");
	assets->addTexture("projectile", "assets/projectile/projectile_test.png");

	assets->addFont("arial", "assets/font/arial.ttf", 16);

	// Map Implementation
	//map = new Map();
	map = new Map("terrain", 3, 32);

	map->loadMap("assets/map/test1.map", 10, 10);

	// Entity Component Systems Implementation
	player.addComponent<TransformComponent>(4);
	player.addComponent<SpriteComponent>("player", true);
	player.addComponent<InputController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	enemy.addComponent<TransformComponent>(4);
	enemy.addComponent<SpriteComponent>("enemy");
	enemy.addGroup(groupEnemies);

	SDL_Color white = { 255, 255, 255, 255 };
	label.addComponent<UILabel>(10, 10, "Hello World!", "arial", white);

	assets->createProjectile(Vector2D(100, 300), Vector2D(2, 1), 200, 2, "projectile");
	assets->createProjectile(Vector2D(100, 400), Vector2D(2, 0), 200, 2, "projectile");
	assets->createProjectile(Vector2D(100, 500), Vector2D(2, -1), 200, 2, "projectile");


	/*wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 2);
	wall.addComponent<SpriteComponent>("assets/wall.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/


	//playerTex = TextureManager::LoadTexture("assets/sam.png", renderer);	// assigns player texture using TextureManager class
}

// creates a list of objects in a group
auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& enemies(manager.getGroup(Game::groupEnemies));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

// Check TransformComponent
//		 SpriteComponent::update()
//		 TileComponent

// Update A.2; Static Camera
//void Game::update()
//{
//	manager.refresh();
//	manager.update();
//
//	if (player.getComponent<TransformComponent>().position.x <= 800 / 4)
//	{
//		camera.x = 400 / 4;
//		std::cout << "(" << camera.x << "," << camera.y << ")" << std::endl;
//	}
//	else if (player.getComponent<TransformComponent>().position.x <= 800 / 4 * 2)
//	{
//		camera.x = 400 / 4 * 2;
//	}
//	else if (player.getComponent<TransformComponent>().position.x <= 800 / 4 * 3)
//	{
//		camera.x = 400 / 4 * 3;
//	}
//	else if (player.getComponent<TransformComponent>().position.x <= 800 / 4 * 4)	// possibly redundant
//	{
//		camera.x = 400 / 4 * 4;
//	}
//	if (player.getComponent<TransformComponent>().position.y <= 640 / 4)
//	{
//		camera.y = 320 / 8;
//	}
//	else if (player.getComponent<TransformComponent>().position.y <= 640 / 4 * 2)
//	{
//		camera.y = 320 / 8 * 3;
//	}
//	else if (player.getComponent<TransformComponent>().position.y <= 640 / 4 * 3)
//	{
//		camera.y = 320 / 8 * 5;
//	}
//	else if (player.getComponent<TransformComponent>().position.y <= 640 / 4 * 4)	// possibly redundant
//	{
//		camera.y = 320 / 8 * 7;
//	}
//
//	if (camera.x < 0)
//	{
//		camera.x = 0;
//	}
//	else if (camera.x > camera.w)
//	{
//		camera.x = camera.w;
//	}
//	if (camera.y < 0)
//	{
//		camera.y = 0;
//	}
//	else if (camera.y > camera.w)
//	{
//		camera.y = camera.w;
//	}
//}

//// Update A; Static Camera
//void Game::update()
//{
//	//map->loadMap();
//	manager.refresh();
//	manager.update();
//
//	if (enemy.getComponent<TransformComponent>().position.x > 500)
//	{
//		enemy.getComponent<SpriteComponent>().setTexture("assets/ghost_attack.png");
//		enemy.getComponent<TransformComponent>().position.add(Vector2D(3, 0));
//	}
//	else
//	{
//		enemy.getComponent<TransformComponent>().position.add(Vector2D(2, 1));
//	}
//
//	//for (auto cc : colliders)
//	//{
//	//	if (Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
//	//	{
//	//		player.getComponent<TransformComponent>().velocity * -1;	// reverses the velocity vector
//	//		std::cout << "Wall Hit!" << endl;
//	//	}
//	//}
//
//
//	counter++;
//	//scale = 4;
//	//destR.h = 16 * scale;	// sets destination rectangle height to 16 * resolution scale
//	//destR.w = 16 * scale;	// sets destination rectangle width to 16 * resolution scale
//	//destR.x = counter;	// sets destination rectangle x position to ...
//
//	if (counter % 60 == 0)	// updates on 60 ticks
//	{
//		counter = 0;
//	}
//	//std::cout << counter << std::endl;
//}

// Update B.2; Camera Follows Player
void Game::update() {

	SDL_Rect playerCollider = player.getComponent<ColliderComponent>().collider;
	Vector2D playerPos = player.getComponent<TransformComponent>().position;
	
	std::stringstream ss;	// output string variable
	ss << "Player Position: " << playerPos;
	label.getComponent<UILabel>().setLabelText(ss.str(), "arial");

	manager.refresh();
	manager.update();

	for (auto& c : colliders)
	{
		SDL_Rect cCollider = c->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(cCollider, playerCollider))
		{
			player.getComponent<TransformComponent>().position = playerPos;
		}
	}

	for (auto& p : projectiles) {
		SDL_Rect projectileCollider = p->getComponent<ColliderComponent>().collider;
		if (Collision::AABB(playerCollider, projectileCollider))
		{
			std::cout << "Hit player!" << std::endl;
			p->destroy();
		}
	}

	camera.x = player.getComponent<TransformComponent>().position.x - 400;
	camera.y = player.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
	{
		camera.x = 0;
	}
	else if (camera.x > camera.w)
	{
		camera.x = camera.w;
	}
	if (camera.y < 0)
	{
		camera.y = 0;
	}
	else if (camera.y > camera.w)
	{
		camera.y = camera.w;
	}
}

// Update B; Camera Follows Player
//void Game::update()
//{
//	//map->loadMap();
//	manager.refresh();
//	manager.update();
//
//	// Camera Follows Player
//	Vector2D pVelocity = player.getComponent<TransformComponent>().velocity;
//	int pSpeed = player.getComponent<TransformComponent>().speed;
//
//	for (auto t : tiles)
//	{
//		t->getComponent<TileComponent>().destRect.x += -(pVelocity.x * pSpeed);
//		t->getComponent<TileComponent>().destRect.y += -(pVelocity.y * pSpeed);
//	}
//}

void Game::handleEvents()
{
	SDL_PollEvent(&event); // dereference memory address of event
	switch (event.type) {	// check event type
		case SDL_QUIT:	// close out window sets program isRunning false
			isRunning = false;
			break;

		default:
			break;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);	// clears renderer
	
	// add stuff to render
	for (auto& t : tiles) {
		t->draw();
	}

	for (auto& c : colliders) {
		c->draw();
	}

	for (auto& p : players) {
		p->draw();
	}

	for (auto& e : enemies) {
		e->draw();
	}

	for (auto& p : projectiles) {
		p->draw();
	}

	label.draw();

	//SDL_RenderCopy(renderer, playerTex, NULL, &destR);	// copies renderer and texture to destination rectangle
	SDL_RenderPresent(renderer); // backbuffer for next render call
}

void Game::clean()
{
	SDL_DestroyWindow(window);	// destroys window
	SDL_DestroyRenderer(renderer);	// destroys renderer
	SDL_Quit();	// quits out of library subsystems
	std::cout << "Game cleaned!" << std::endl;
}