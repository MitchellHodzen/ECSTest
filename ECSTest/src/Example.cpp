#include "Example.h"
#include <iostream>
#include "kecs/KECS.h"
#include "Components/c_transform.h"
#include "Components/c_rect.h"
#include "Tags.h"
#include "Components/c_input.h"
#include "Components/c_physics.h"
#include "Time.h"
#include "RenderSystem.h"
#include "ResourceManager.h"
#include "Components/c_sprite.h"
#include "InputSystem.h"
#include "CollisionSystem.h"
#include "PhysicsSystem.h"
#include "Factories/PlayerShipFactory.h"
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
	delete inputSystem;
	delete renderSystem;
	delete collisionSystem;
	delete physicsSystem;
	delete bulletSystem;
}


void Example::Run(){

	EntityManager::SetUpComponents<Transform, Rect, UserInput, Sprite, Physics, Cannon>();
	EntityManager::SetUpTags<Player, Enemy, Wall>();

	Entity player1 = PlayerShipFactory::ConstructPlayerShip(0, 0);

	while (!quit)
	{
		Time::CalculateDeltaTime();

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
