#ifndef STOVE_H
#define STOVE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "assetmanager.h"
#include "npc.h"

#define STOVE_COOK_TIME 7

class Stove : public NPC
{
private:

  float cookingTime;
  bool isCooking;
  bool isDone;
public:

  Stove(SDL_Renderer* r);
  virtual void interact(Item* holding);
  virtual void update(double deltaTime);
};

#endif
