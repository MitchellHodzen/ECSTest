#include "Texture.h"
#include "Renderer.h"

Texture::Texture()
{
	sdlTexture = NULL;
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	FreeTexture();
}

bool Texture::LoadTexture(std::string path, Renderer* renderer)
{
	bool success = true;
	FreeTexture();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		std::cout << "Unable to load image at path: " << path << " SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		sdlTexture = SDL_CreateTextureFromSurface(renderer->GetSdlRenderer(), loadedSurface);
		if (sdlTexture == NULL)
		{
			std::cout << "Unable to create texture. SDL error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			width = loadedSurface->w;
			height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	return success;
}

void Texture::FreeTexture()
{
	if (sdlTexture != NULL)
	{
		SDL_DestroyTexture(sdlTexture);
		sdlTexture = NULL;
		width = 0;
		height = 0;
	}
}

int Texture::GetWidth()
{
	return width;
}
int Texture::GetHeight()
{
	return height;
}
void Texture::Render(int posX, int posY, SDL_Rect* cutRect, SDL_Renderer* renderer, SDL_RendererFlip flip)
{
	//flip defaults to SDL_FLIP_NONE
	if (cutRect == NULL || cutRect == nullptr)
	{
		std::cout << "cutRect is null" << std::endl;
	}
	else if (renderer == NULL || renderer == nullptr)
	{
		std::cout << "renderer is null" << std::endl;
	}
	else
	{
		//If we want the position to be the middle, do this calculation
		//SDL_Rect rect{ posX - cutRect->w / 2, posY - cutRect->h / 2, cutRect->w, cutRect->h };

		//If we want the position to be the top left do this calcuation
		SDL_Rect rect{ posX, posY, cutRect->w, cutRect->h };

		//Not a memory leak? Memory is just slowly allocated but has an upper bounds
		SDL_RenderCopyEx(renderer, sdlTexture, cutRect, &rect, 0.0, NULL, flip);
	}
}