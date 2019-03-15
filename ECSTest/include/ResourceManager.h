#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;

class ResourceManager
{
public:
	static ResourceManager& GetInstance();
	~ResourceManager();
	bool Initialize();
	Texture* GetTexture(std::string key);
private:
	static ResourceManager instance;
	std::unordered_map<std::string, Texture*>* texturePointerMap = new std::unordered_map<std::string, Texture*>();;

	ResourceManager();
	bool LoadSprites();
	void UnloadSprites();
	bool LoadSprite(std::string path, std::string key);
};

