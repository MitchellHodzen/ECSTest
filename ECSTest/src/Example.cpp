#include "Example.h"
#include <iostream>
#include "kecs/KECS.h"
#include "Components/c_position.h"
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

	EntityManager::SetUpComponents<Position, Rect, UserInput, Sprite, Physics>();
	EntityManager::SetUpTags<Player, Enemy, Wall>();

	int ent0 = EntityManager::CreateEntity();
	EntityManager::AddTag<Player>(ent0);
	EntityManager::AddComponent<Position>(ent0);
	EntityManager::AddComponent<Rect>(ent0);
	EntityManager::AddComponent<UserInput>(ent0);
	//EntityManager::AddComponent<Sprite>(ent0);
	Rect rect;
	rect.width = 50;
	rect.height = 50;
	rect.offsetX = -rect.width / 2;
	rect.offsetY = -rect.height / 2;
	EntityManager::SetComponent<Rect>(ent0, rect);

	Sprite sprite;
	sprite.texture = resourceManager->GetTexture("Ship1");
	EntityManager::SetComponent<Sprite>(ent0, sprite);

	Physics physics;
	physics.maxSpeed = 200;
	EntityManager::SetComponent<Physics>(ent0, physics);

	Rect boxRect;
	boxRect.width = 100;
	boxRect.height = 100;
	Position initialBoxPosition;
	initialBoxPosition.x = 100;
	initialBoxPosition.y = 400;

	int numHBoxes = 5;
	for (int i = 0; i < numHBoxes; ++i)
	{
		int entity = EntityManager::CreateEntity();
		EntityManager::AddComponent<Position>(entity);
		EntityManager::AddComponent<Rect>(entity);
		Position& pos = EntityManager::GetComponent<Position>(entity);
		pos.x = initialBoxPosition.x + boxRect.width * i;
		pos.y = initialBoxPosition.y;
		EntityManager::SetComponent<Rect>(entity, boxRect);
		EntityManager::SetComponent<Sprite>(entity, sprite);
	}
	int numVBoxes = 3;
	for (int i = 0; i < numVBoxes; ++i)
	{
		int entity = EntityManager::CreateEntity();
		EntityManager::AddComponent<Position>(entity);
		EntityManager::AddComponent<Rect>(entity);
		Position& pos = EntityManager::GetComponent<Position>(entity);
		pos.x = initialBoxPosition.x;
		pos.y = initialBoxPosition.y - boxRect.height * i;
		EntityManager::SetComponent<Rect>(entity, boxRect);
		EntityManager::SetComponent<Sprite>(entity, sprite);

	}

	float deltaTime = 0.0f;
	Uint32 lastFrameTime = 0;
	Uint32 currentFrameTime = SDL_GetTicks();

	while (!quit)
	{
		lastFrameTime = currentFrameTime;
		currentFrameTime = SDL_GetTicks();
		Time::CalculateDeltaTime(lastFrameTime, currentFrameTime);

		inputSystem->GetUserInput();
		physicsSystem->HandleUserInput();
		physicsSystem->ApplyHorizontalPhysics();
		collisionSystem->CheckCollisions();
		physicsSystem->HandleHorizontalCollisions();
		physicsSystem->ApplyVerticalPhysics();
		collisionSystem->CheckCollisions();
		physicsSystem->HandleVerticalCollisions();
		renderSystem->Draw();
	}
}

void Example::SetUp() {
	renderSystem = new RenderSystem(screenWidth, screenHeight);
	resourceManager = new ResourceManager(renderSystem);
	inputSystem = new InputSystem();
	collisionSystem = new CollisionSystem();
	physicsSystem = new PhysicsSystem();
}
