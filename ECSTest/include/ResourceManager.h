#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();
private:
	std::unordered_map<std::string, Texture*>* texturePointerMap;

	void LoadSprites();
	void UnloadSprites();
};

