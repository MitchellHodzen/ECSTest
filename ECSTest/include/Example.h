#pragma once
#include <SDL.h>

class InputSystem;
class ResourceManager;
class RenderSystem;
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
	bool quit = false;

	InputSystem* inputSystem;
	ResourceManager* resourceManager;
	RenderSystem* renderSystem;
	CollisionSystem* collisionSystem;
	PhysicsSystem* physicsSystem;
};

