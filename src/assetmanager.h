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

#define FONT_TEXTURE_SIZE 512
#define NUM_CHARS 128

struct Font
{
  TTF_Font* font;
  SDL_Texture* tex;
  int size;
  SDL_FRect glyphs[NUM_CHARS];
};

class AssetManager
{
private:

  std::unordered_map<std::string, int> textureIDs;
  std::unordered_map<std::string, int> fontIDs;

  std::vector<SDL_Texture*> textures;
  std::vector<Font> fonts;

  AssetManager();
  ~AssetManager();

public:
  AssetManager(const AssetManager& obj) = delete; 

  bool addTexture(SDL_Renderer* r, std::string name, std::string path);
  bool addFont(SDL_Renderer* r, std::string name, std::string path, int size);

  int getTextureID(std::string name);
  SDL_Texture* getTexture(int ID);
  SDL_Texture* getTexture(std::string name);

  int getFontID(std::string name);
  Font getFont(int ID);
  Font getFont(std::string name);
  
  static AssetManager& getInstance();
};

#endif
