#ifndef STRIP_H
#define STRIP_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "raycast.h"

#define WALL_HEIGHT 800
#define WALL_TEX_PATH "assets/images/walls.png"
#define WALL_TEX_SIZE 64


class Strip
{
private:
  static SDL_Texture* wallTex;
  static SDL_Renderer* renderer;
  SDL_FRect srcRect;
  SDL_FRect drawRect;

  float dist;
  float height;

  bool enabled = false;

public:
  static bool loadWallTexture(SDL_Renderer* r);
  static void free();
  Strip();
  Strip(RaycastResult ray, vec2 pos, float rot, int screenWidth, int screenHeight, int quality, int fov);
  bool isEnabled();
  float getHeight();
  float getDist();
  void draw();
};

#endif
