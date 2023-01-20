#include "GameObject.h"
#include "TextureManager.h"

//GameObject::GameObject(const char* textureSheet, int x, int y)
//{
//	objTex = TextureManager::loadTexture(textureSheet);
//
//	xPos = x;
//	yPos = y;
//
//}
//
//GameObject::~GameObject()
//{
//
//}
//
//void GameObject::update()
//{
//	xPos++;
//	yPos++;
//
//	srcRect.h = 16;
//	srcRect.w = 16;
//	srcRect.x = 0;
//	srcRect.y = 0;
//
//	destRect.x = xPos;
//	destRect.y = yPos;
//	destRect.w = 64;
//	destRect.h = 64;
//	//std::cout << "GameObject updated" << std::endl;
//
//}
//
//void GameObject::render()
//{
//	SDL_RenderCopy(Game::renderer, objTex, &srcRect, &destRect);
//	//std::cout << "GameObject rendered" << std::endl;
//}