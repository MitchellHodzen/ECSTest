#pragma once

struct Rect;
struct Position;

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();
	void CheckCollisions();
	void HandleHorizontalCollisions();
	void HandleVerticalCollisions();
private:
	bool RectsColliding(Rect rect1, Position pos1, Rect rect2, Position pos2);

};

