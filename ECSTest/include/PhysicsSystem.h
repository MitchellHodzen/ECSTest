#pragma once
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void HandleUserInput();
	void ApplyPhysics();
	void HandleCollisions();
};

