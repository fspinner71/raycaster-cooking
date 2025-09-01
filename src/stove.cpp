#include "stove.h"
#include "interaction.h"

Stove::Stove(SDL_Renderer* r) : NPC(r, AssetManager::getInstance().getTextureID("stove"), InteractionID::None)
{
  getSprite()->setSize({500, 500});
  getSprite()->setZOffset(-250);
  getSprite()->setFrameWidth(64);
  getSprite()->setFrameIndex(0);
  
  cookingTime = 0.f;
  isCooking = false;
  isDone = false;
}

void Stove::update(double deltaTime)
{
  NPC::update(deltaTime);

  if(isCooking)
  {
    cookingTime += deltaTime;

    getSprite()->setFrameIndex(1);

    if(cookingTime >= STOVE_COOK_TIME)
    {
      isCooking = false;
      isDone = true;
    }
  } else if(isDone)
  {
    isCooking = false;
    getSprite()->setFrameIndex(2);
  } else {
    getSprite()->setFrameIndex(0);
  }
}

void Stove::interact(Item* holding)
{
  NPC::interact(holding);
  if(!(isCooking || isDone) && *holding == Item::RawPatty)
  {
    *holding = Item::None;
    isCooking = true;
  } else if(*holding == Item::None)
  { 
    if(isDone)
    {
      *holding = Item::CookedPatty;
    } else {
      *holding = Item::RawPatty;
    }
    isDone = false;
    cookingTime = 0.f;
    isCooking = false;
  }
}
