#include "assetmanager.h"

AssetManager& AssetManager::getInstance()
{
  static AssetManager instance;
  return instance;
}

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
  for(int i = 0; i < textures.size(); i++)
  {
    SDL_DestroyTexture(textures.at(i));
  }
}

bool AssetManager::addTexture(SDL_Renderer* r, std::string name, std::string path)
{
  SDL_Texture* tex = IMG_LoadTexture(r, path.c_str());
  if(!tex)
  {
    std::cout << "Could not load " << name << ": " << SDL_GetError() << std::endl;
    return false;
  }

  if(!SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST))
  {
    std::cout << "Could not set " << name << "scale mode: " << SDL_GetError() << std::endl;
    return false;
  }

  textures.push_back(tex);
  textureIDs.insert(std::make_pair(name, textures.size() - 1));

  return true;
}

int AssetManager::getTextureID(std::string name)
{
  return textureIDs.at(name);
}

SDL_Texture* AssetManager::getTexture(int ID)
{
  return textures.at(ID);
}

SDL_Texture* AssetManager::getTexture(std::string name)
{
  return getTexture(getTextureID(name));
}
