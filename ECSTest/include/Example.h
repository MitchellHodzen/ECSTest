#pragma once
#include <SDL.h>
struct Rect;
struct Position;

class InputManager;
class ResourceManager;
class Renderer;
class CollisionSystem;

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
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
	static void Test();
	bool quit = false;

	InputManager* inputManager;
	ResourceManager* resourceManager;
	Renderer* renderer;
	CollisionSystem* collisionSystem;
};

