#pragma once
#include <SDL.h>
struct Rect;
struct Position;

class InputManager;
class ResourceManager;
class Renderer;
class CollisionSystem;
class PhysicsSystem;

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
	void HandleUserInput();
	static void Test();
	bool quit = false;

	InputManager* inputManager;
	ResourceManager* resourceManager;
	Renderer* renderer;
	CollisionSystem* collisionSystem;
	PhysicsSystem* physicsSystem;
};

