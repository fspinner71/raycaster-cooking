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
  for(int i = 0; i < fonts.size(); i++)
  {
    SDL_DestroyTexture(fonts.at(i).tex);
    TTF_CloseFont(fonts.at(i).font);
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

bool AssetManager::addFont(SDL_Renderer* r, std::string name, std::string path, int size)
{
  Font newFont;

  TTF_Font* font = TTF_OpenFont(path.c_str(), 70);
  newFont.font = font;

  if(!font)
  {
    std::cout << "Could not load " << name << ": " << SDL_GetError() << std::endl;
    return false;
  }

  std::string chars = "";
  for(int i = ' '; i <= 'z'; i++)
  {
    chars += (char)i;
    chars += " ";
  }
  SDL_Surface *surface = TTF_RenderText_Solid(font, chars.c_str(), 0, {255, 255, 255, 255});

  if(!surface)
  {
    std::cout << "Could not create surface " << name << ": " << SDL_GetError() << std::endl;
    return false;
  }

  newFont.tex = SDL_CreateTextureFromSurface(r, surface);

  if(!newFont.tex)
  {
    std::cout << "Could not create texture from font " << name << ": " << SDL_GetError() << std::endl;
    return false;
  }

  SDL_DestroySurface(surface);
  surface = NULL;

  int totalWidth = 0;
  int currentWidth;
  int height = newFont.tex->h;
  int spaceSize;
  TTF_GetStringSize(font, chars.substr(0, 1).c_str(), 2 * sizeof(char), &spaceSize, NULL);

  for (int j = 0; j < chars.length(); j += 2) 
  {
    // divides by two because we added a space to each character and add 32 because char offset
      int k = j / 2 + 32;
      newFont.glyphs[k].x = totalWidth;
      newFont.glyphs[k].y = 0;
      newFont.glyphs[k].h = height;

      TTF_GetStringSize(font, chars.substr(j, 2).c_str(), 2 * sizeof(char), &currentWidth, NULL);

      newFont.glyphs[k].w = currentWidth - 10;
      totalWidth += currentWidth;
  }

  fonts.push_back(newFont);
  fontIDs.insert(std::make_pair(name, fonts.size() - 1));
  return true;
}

int AssetManager::getFontID(std::string name)
{
  return fontIDs.at(name);
}

Font AssetManager::getFont(int ID)
{
  return fonts.at(ID);
}

Font AssetManager::getFont(std::string name)
{
  return getFont(getFontID(name));
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
