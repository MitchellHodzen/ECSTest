#pragma once
#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	bool LoadTexture(std::string path);
	void FreeTexture();
	void Render(int posX, int posY, SDL_Rect* cutRect, SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int GetWidth();
	int GetHeight();
private:
	SDL_Texture* sdlTexture;
	int width;
	int height;
};

