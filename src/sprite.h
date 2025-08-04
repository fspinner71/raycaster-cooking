#ifndef SPRITE_H
#define SPRITE_H

#include <SDL3/SDL.h>
#include "math.h"

class Sprite
{
private:
  SDL_Renderer* renderer;
  SDL_Texture* tex;
  SDL_FRect srcRect;
  SDL_FRect drawRect;
 
  vec2 pos;
  vec2 size;
  float zOffset;

  int frameWidth;
  int frameIndex;
public:
  Sprite(SDL_Renderer* r, SDL_Texture* t);
  void setPos(vec2 p);
  vec2 getPos();
  void setSize(vec2 s);
  void setSrcRect(SDL_FRect r);
  void setTexture(SDL_Texture* t);
  void setFrameWidth(int w);
  void setFrameIndex(int i);
  void setZOffset(float z);
  float getDist(vec2 p);
  void update(double deltaTime);
  void draw(int screenWidth, int screenHeight, vec2 camPos, float camRot, float fov);
  void free();
};


#endif
