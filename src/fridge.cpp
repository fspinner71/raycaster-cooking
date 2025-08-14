#include "fridge.h"
#include "interaction.h"


Fridge::Fridge(SDL_Renderer* r, Item t) : NPC(r, AssetManager::getInstance().getTextureID("fridge"), InteractionID::None)
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
