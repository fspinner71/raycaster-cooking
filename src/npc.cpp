#include "npc.h"
#include <SDL3_image/SDL_image.h>

NPC::NPC(SDL_Renderer* r, SDL_Texture* t, InteractionID intID)
{

  sprite = new Sprite(r, t);

  interactionID = intID;
}

void NPC::setPos(vec2 p)
{
  pos = p;
}

Sprite* NPC::getSprite()
{
  return sprite;
}

vec2 NPC::getPos()
{
  return pos;
}

float NPC::getDist(vec2 p)
{
  return std::sqrt(std::pow(pos.x - p.x, 2) + std::pow(pos.y - p.y, 2));
}

InteractionID NPC::getInteractionID()
{
  return interactionID;
}

void NPC::setInteractionID(InteractionID i)
{
  interactionID = i;
}
void NPC::interact(Item* holding)
{
}

void NPC::update(double deltaTime)
{
  sprite->setPos(pos);
}

void NPC::draw(int screenWidth, int screenHeight, vec2 camPos, float camRot, float fov)
{
  sprite->draw(screenWidth, screenHeight, camPos, camRot, fov);
}

void NPC::free()
{
  if(sprite)
  {
    sprite->free();
    delete sprite;
  }
}

