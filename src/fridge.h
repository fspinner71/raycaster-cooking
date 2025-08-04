#ifndef FRIDGE_H
#define FRIDGE_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include "npc.h"


class Fridge : public NPC
{
private:
  static SDL_Texture* tex;

  Item type;
public:
  static void loadTexture(SDL_Renderer* r);
  static void free();

  Fridge(SDL_Renderer* r, Item t);
  virtual void interact(Item* holding);
  virtual void update(double deltaTime);
};


#endif
