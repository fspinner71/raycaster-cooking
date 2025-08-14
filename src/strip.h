#ifndef STRIP_H
#define STRIP_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "assetmanager.h"
#include "raycast.h"

#define WALL_HEIGHT 800
#define WALL_TEX_SIZE 64


class Strip
{
private:
  SDL_Renderer* renderer;
  SDL_FRect srcRect;
  SDL_FRect drawRect;

  int tex;

  float dist;
  float height;

  bool enabled = false;

public:
  Strip();
  Strip(SDL_Renderer* r, RaycastResult ray, vec2 pos, float rot, int screenWidth, int screenHeight, int quality, int fov);
  bool isEnabled();
  float getHeight();
  float getDist();
  void draw();
};

#endif
