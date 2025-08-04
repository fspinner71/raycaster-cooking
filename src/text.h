#ifndef TEXT_H
#define TEXT_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <string>
#include "math.h"

#define FONT_TEXTURE_SIZE 512
#define NUM_CHARS 128
#define NUM_FONTS 1
#define COMIC_SANS 0

class Text
{
private:
  static TTF_Font* fonts[NUM_FONTS];
  static SDL_Texture* fontTextures[NUM_FONTS];
  static SDL_FRect glyphs[NUM_FONTS][NUM_CHARS];

  SDL_Renderer* renderer;
  int font;

  std::string text;
  SDL_FRect rect;
  vec3 clr;

  void fitText();

public:
  static void loadFonts(SDL_Renderer* r);
  static void freeFonts();
  Text(SDL_Renderer* r, int f, std::string t);
  void setText(std::string t);
  void setRect(SDL_FRect r);
  void setColor(vec3 c);
  void draw();
  void free();
};

#endif
