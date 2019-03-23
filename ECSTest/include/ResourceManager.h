#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;
class Renderer;

class ResourceManager
{
public:
	ResourceManager(Renderer* renderer);
	~ResourceManager();
	Texture* GetTexture(std::string key);

private:
	std::unordered_map<std::string, Texture*>* texturePointerMap = new std::unordered_map<std::string, Texture*>();;

	bool LoadSprites(Renderer* renderer);
	void UnloadSprites();
	bool LoadSprite(std::string path, std::string key, Renderer* renderer);
};

