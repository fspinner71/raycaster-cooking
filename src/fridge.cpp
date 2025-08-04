#include "fridge.h"
#include "interaction.h"

SDL_Texture* Fridge::tex = NULL;

void Fridge::loadTexture(SDL_Renderer* r)
{
  tex = IMG_LoadTexture(r, "assets/images/fridge.png");
  SDL_SetTextureScaleMode(tex, SDL_SCALEMODE_NEAREST);
}
void Fridge::free()
{
  if(tex)
  {
    SDL_DestroyTexture(tex);
    tex = NULL;
  }
}

Fridge::Fridge(SDL_Renderer* r, Item t) : NPC(r, tex, InteractionID::None)
{
  getSprite()->setSize({1000, 1000});
  getSprite()->setZOffset(0);
  getSprite()->setFrameWidth(64);
  getSprite()->setFrameIndex(0);

  type = t;
 }

void Fridge::update(double deltaTime)
{
  NPC::update(deltaTime);
}

void Fridge::interact(Item* holding)
{
  NPC::interact(holding);

  if(*holding == Item::None)
  {
    *holding = type;
  }
}
