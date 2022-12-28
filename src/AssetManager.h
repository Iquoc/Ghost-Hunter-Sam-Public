#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS\ECS.h"
#include "SDL_ttf.h"
//#include "ECS\Components.h"   ... caused "use of undefined object" error

class AssetManager
{
public:
	AssetManager(Manager* assManager);
	~AssetManager();

	// Game Objects
	void createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id);

	// Texture Management
	void addTexture(std::string id, const char* filePath);
	SDL_Texture* getTexture(std::string id);

	void addFont(std::string id, std::string filePath, int fontSize);
	TTF_Font* getFont(std::string id);

private:
	Manager* manager;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, TTF_Font*> fonts;
};