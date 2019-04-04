#pragma once
class PlayerShipFactory
{
public:
	static int ConstructPlayerShip(int posX, int posY);
private:
	PlayerShipFactory() {}
	~PlayerShipFactory() {}
};

