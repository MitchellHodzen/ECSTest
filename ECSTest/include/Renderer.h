#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Renderer
{
public:
	static Renderer& GetInstance();
	~Renderer();
	void Render();
	void Draw();
	bool Initialize(int screenWidth, int screenHeight);
	int GetScreenWidth();
	int GetScreenHeight();
private:
	static Renderer instance;
	SDL_Renderer* sdlRenderer = nullptr;
	SDL_Window* sdlWindow = nullptr;
	int screenWidth;
	int screenHeight;

	Renderer();
};

