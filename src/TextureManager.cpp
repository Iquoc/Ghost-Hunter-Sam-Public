#include "TextureManager.h"
#include "Game.h"

SDL_Texture* TextureManager::loadTexture(const char* texture)
{
	SDL_Surface* tempSurface = IMG_Load(texture);	// loads the image as a collection of pixels
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);		// uses surface to create texture
	SDL_FreeSurface(tempSurface);	// frees the surface

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip)
{
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &destRect, NULL, NULL, flip);
}