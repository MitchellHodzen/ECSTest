#pragma once
class PhysicsSystem
{
public:
	PhysicsSystem();
	~PhysicsSystem();
	void ApplyHorizontalPhysics();
	void ApplyVerticalPhysics();
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
};

