#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>


class AssetManager
{
private:

  std::unordered_map<std::string, int> textureIDs;

  std::vector<SDL_Texture*> textures;

  AssetManager();
  ~AssetManager();

public:
  AssetManager(const AssetManager& obj) = delete; 

  bool addTexture(SDL_Renderer* r, std::string name, std::string path);
  bool createFontTexture(SDL_Renderer* r, std::string name, std::string path, int size);

  int getTextureID(std::string name);
  SDL_Texture* getTexture(int ID);
  SDL_Texture* getTexture(std::string name);
  
  static AssetManager& getInstance();
};

#endif
