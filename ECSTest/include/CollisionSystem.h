#pragma once

struct Rect;
struct Position;

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();
	void CheckCollisions();
private:
	bool RectsColliding(Rect rect1, Position pos1, Rect rect2, Position pos2);

};

