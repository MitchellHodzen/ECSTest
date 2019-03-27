#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;
class RenderSystem;

class ResourceManager
{
public:
	ResourceManager(RenderSystem* renderSystem);
	~ResourceManager();
	Texture* GetTexture(std::string key);

private:
	std::unordered_map<std::string, Texture*>* texturePointerMap = new std::unordered_map<std::string, Texture*>();;

	bool LoadSprites(RenderSystem* renderSystem);
	void UnloadSprites();
	bool LoadSprite(std::string path, std::string key, RenderSystem* renderSystem);
};

