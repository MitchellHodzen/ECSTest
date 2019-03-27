#pragma once
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void HandleUserInput();
	void ApplyHorizontalPhysics();
	void ApplyVerticalPhysics();
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
};

