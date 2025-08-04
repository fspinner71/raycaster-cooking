#ifndef STOVE_H
#define STOVE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "npc.h"

#define STOVE_COOK_TIME 7

class Stove : public NPC
{
private:
  static SDL_Texture* tex;

  float cookingTime;
  bool isCooking;
  bool isDone;
public:
  static void loadTexture(SDL_Renderer* r);
  static void free();

  Stove(SDL_Renderer* r);
  virtual void interact(Item* holding);
  virtual void update(double deltaTime);
};

#endif
