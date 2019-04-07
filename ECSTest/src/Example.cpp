#include "Example.h"
#include <iostream>
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_rect.h"
#include "Tags.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "Time.h"
#include "MessageManager.h"
#include "Messages/m_collision.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "Components/c_sprite.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "Factories/PlayerShipFactory.h"
#include "Factories/BulletFactory.h"
#include "Components/c_cannon.h"
#include "BulletSystem.h"

Example::Example(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	SetUp();
}


Example::~Example()
{
}


void Example::Run(){

	EntityManager::SetUpComponents<Transform, Rect, UserInput, Sprite, Physics, Cannon>();
	EntityManager::SetUpTags<Player, Enemy, Wall>();

	Entity player1 = PlayerShipFactory::ConstructPlayerShip(0, 0);


	float deltaTime = 0.0f;
	Uint32 lastFrameTime = 0;
	Uint32 currentFrameTime = SDL_GetTicks();

	while (!quit)
	{
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetTicks();
		Time::CalculateDeltaTime(lastFrameTime, currentFrameTime);

		inputSystem->GetUserInput();
		inputSystem->HandleUserInput();
		physicsSystem->ApplyPhysics();
		bulletSystem->FireBullets();
		collisionSystem->CheckCollisions();
		physicsSystem->HandleCollisions();
		renderSystem->Draw();
	}
}

void Example::SetUp() {
	renderSystem = new RenderSystem(screenWidth, screenHeight);
	ResourceManager::GetInstance().Initialize(renderSystem);
	inputSystem = new InputSystem();
	collisionSystem = new CollisionSystem();
	physicsSystem = new PhysicsSystem();
	bulletSystem = new BulletSystem();
}
