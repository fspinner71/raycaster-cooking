#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <string>
#include "math.h"
#include "assetmanager.h"

class Text
{
private:
  SDL_Renderer* renderer;
  int font;

  std::string text;
  SDL_FRect rect;
  vec3 clr;

  void fitText();

public:
  Text(SDL_Renderer* r, int f, std::string t);
  Text(SDL_Renderer* r, std::string fontName, std::string t);
  void setFont(std::string name);
  void setFont(int ID);
  void setText(std::string t);
  void setRect(SDL_FRect r);
  void setColor(vec3 c);
  void draw();
  void free();
};

#endif
