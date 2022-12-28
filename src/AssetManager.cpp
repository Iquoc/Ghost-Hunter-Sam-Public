#include "AssetManager.h"
#include "ECS\Components.h"

AssetManager::AssetManager(Manager* assManager) : manager(assManager)
{

}

AssetManager::~AssetManager()
{

}

void AssetManager::createProjectile(Vector2D pos, Vector2D vel, int range, int speed, std::string id)
{
	auto& projectile(manager->addEntity());
	projectile.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 1);
	projectile.addComponent<SpriteComponent>(id, false);
	projectile.addComponent<ProjectileComponent>(range, speed, vel);
	projectile.addComponent<ColliderComponent>("projectile");
	projectile.addGroup(Game::groupProjectiles);
}

void AssetManager::addTexture(std::string id, const char* filePath)
{
	textures.emplace(id, TextureManager::loadTexture(filePath));
}

SDL_Texture* AssetManager::getTexture(std::string id)
{
	return textures[id];
}

void AssetManager::addFont(std::string id, std::string filePath, int fontSize)
{
	fonts.emplace(id, TTF_OpenFont(filePath.c_str(), fontSize));
}

TTF_Font* AssetManager::getFont(std::string id)
{
	return fonts[id];
}

