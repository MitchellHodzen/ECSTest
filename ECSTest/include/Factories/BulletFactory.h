#pragma once
#include "kecs/KECS.h"
class BulletFactory
{
public:
	static Entity ConstructBullet(int posX, int posY);
private:
	BulletFactory() {}
	~BulletFactory() {}
};

