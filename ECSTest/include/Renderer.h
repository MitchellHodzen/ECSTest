#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Renderer
{
public:
	Renderer(int screenWidth, int screenHeight);
	~Renderer();
	void Render();
	void Draw();
	bool Initialize(int screenWidth, int screenHeight);
	int GetScreenWidth();
	int GetScreenHeight();
	SDL_Renderer* GetSdlRenderer();

private:
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Window* sdlWindow = nullptr;
	int screenWidth;
	int screenHeight;
};

