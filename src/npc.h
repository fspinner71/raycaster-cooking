#ifndef NPC_H
#define NPC_H

#include <SDL3/SDL.h>
#include "math.h"
#include "sprite.h"
#include "interaction.h"

class NPC
{
private:
  Sprite* sprite; 

  vec2 pos;

  InteractionID interactionID;
public:
  static void loadTextures();
  static void NPCFree();
  NPC(SDL_Renderer* r, SDL_Texture* t, InteractionID intID);
  void setPos(vec2 p);
  vec2 getPos();
  float getDist(vec2 p);
  InteractionID getInteractionID();
  Sprite* getSprite();
  void setInteractionID(InteractionID i);
  virtual void update(double deltaTime);
  void draw(int screenWidth, int screenHeight, vec2 camPos, float camRot, float fov);
  void free();

  virtual void interact(Item* holding);
};

#endif
