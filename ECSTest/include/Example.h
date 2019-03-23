#pragma once
#include <SDL.h>
struct Rect;
struct Position;

class InputManager;
class ResourceManager;
class Renderer;

class Example
{
public:
	Example(int screenWidth, int screenHeight);
	void Run();
	~Example();
private:
	void SetUp();

	int screenWidth;
	int screenHeight;
	void ApplyHorizontalPhysics();
	void ApplyVerticalPhysics();
	void HandleUserInput();
	void CheckCollisions();
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
	bool RectsColliding(Rect rect1, Position pos1, Rect rect2, Position pos2);
	static void Test();
	bool quit = false;

	InputManager* inputManager;
	ResourceManager* resourceManager;
	Renderer* renderer;
};

