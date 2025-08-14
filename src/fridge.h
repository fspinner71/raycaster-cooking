#ifndef FRIDGE_H
#define FRIDGE_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "assetmanager.h"
#include "npc.h"


class Fridge : public NPC
{
private:

  Item type;
public:

  Fridge(SDL_Renderer* r, Item t);
  virtual void interact(Item* holding);
  virtual void update(double deltaTime);
};


#endif
