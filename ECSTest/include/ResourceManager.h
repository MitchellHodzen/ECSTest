#pragma once
#include <unordered_map>
#include <string>

//Forward declarations
class Texture;
class RenderSystem;

class ResourceManager
{
public:
	enum class SpriteKey { Player, Bullet };

	ResourceManager(RenderSystem* renderSystem);
	~ResourceManager();
	Texture* GetTexture(SpriteKey key);

private:
	std::unordered_map<SpriteKey, Texture*>* texturePointerMap = new std::unordered_map<SpriteKey, Texture*>();;

	bool LoadSprites(RenderSystem* renderSystem);
	void UnloadSprites();
	bool LoadSprite(std::string path, SpriteKey key, RenderSystem* renderSystem);
};

