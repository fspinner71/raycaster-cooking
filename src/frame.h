#ifndef FRAME_H
#define FRAME_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "math.h"

class Frame
{
private:
  SDL_Renderer* renderer;
  SDL_FRect rect;
  vec4 clr;

public:
  Frame(SDL_Renderer* r);
  void setRect(SDL_FRect r);
  void setColor(vec4 c);
  void draw();
};

#endif
