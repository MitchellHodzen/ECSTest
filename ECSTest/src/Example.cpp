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

	EntityManager::SetUpComponents<Transform, Rect, UserInput, Sprite, Physics>();
	EntityManager::SetUpTags<Player, Enemy, Wall>();

	int ent0 = EntityManager::CreateEntity();
	EntityManager::AddTag<Player>(ent0);
	EntityManager::AddComponent<Transform>(ent0);
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
	sprite.texture = ResourceManager::GetInstance().GetTexture(ResourceManager::SpriteKey::Player);
	EntityManager::SetComponent<Sprite>(ent0, sprite);

	Physics physics;
	physics.maxSpeed = 200;
	EntityManager::SetComponent<Physics>(ent0, physics);

	int bullet1 = EntityManager::CreateEntity();
	Transform bulletTransform;
	bulletTransform.position.SetValues(300, 300);
	EntityManager::SetComponent<Transform>(bullet1, bulletTransform);
	Sprite bulletSprite;
	bulletSprite.texture = ResourceManager::GetInstance().GetTexture(ResourceManager::SpriteKey::Bullet);
	EntityManager::SetComponent<Sprite>(bullet1, bulletSprite);
	Physics bulletPhysics;
	bulletPhysics.velocity.SetValues(0, -500);
	bulletPhysics.maxSpeed = 200;
	EntityManager::SetComponent<Physics>(bullet1, bulletPhysics);


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
		physicsSystem->ApplyPhysics();
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
}
