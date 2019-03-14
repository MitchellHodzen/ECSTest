#include "ResourceManager.h"
#include "Texture.h"


ResourceManager::ResourceManager()
{
	LoadSprites();
}


ResourceManager::~ResourceManager()
{
	UnloadSprites();
}

void ResourceManager::LoadSprites()
{
	texturePointerMap = new std::unordered_map<std::string, Texture*>();
	Texture* shipTexture = new Texture();

}

void ResourceManager::UnloadSprites()
{

}
