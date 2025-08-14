#ifndef PLAYER_H
#define PLAYER_H

#include <SDL3/SDL_scancode.h>
#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <math.h>
#include "math.h"
#include "scene.h"
#include "canvas.h"
#include "raycast.h"
#include "interaction.h"

#define PLAYER_SPEED 2
#define PLAYER_COLOR 0, 255, 0, 255

#define PLAYER_RAY_HIT_COLOR 255, 0, 0, 255
#define PLAYER_RAY_MISS_COLOR 255, 255, 255, 255

#define PLAYER_RECT_W 20
#define PLAYER_RECT_H 20

#define PLAYER_SENSITIVITY 0.1

#define PLAYER_INTERACT_ANGLE 90
#define PLAYER_INTERACT_DISTANCE 1

#define HOLDING_ITEM_SCALE 20
#define HOLDING_ITEM_OFFSET_X 350
#define HOLDING_ITEM_OFFSET_Y 500

#define HOLDING_WALK_AMPLITUDE_Y 100
#define HOLDING_WALK_AMPLITUDE_X 100
#define HOLDING_WALK_FREQUENCY 10

enum class States
{
  Interacting,
  Walking,
  
  Count
};

class Player
{
private:
  SDL_Renderer* renderer;
  
  Scene* scene;
  Canvas* canvas;

  int* width;
  int* height;

  int itemTextures[(int)Item::Count];

  vec2 pos;

  SDL_FRect drawRect;

  vec2 vel;
  vec2 lookDir;

  float rVel;
  float rot;

  float rSpeed;
  float speed;

  NPC* currentInteract;
  Interaction interaction;
  
  bool states[(int)States::Count];

  float timeWalking;

  Item holding;

  const bool* keystates;
public:
  Player(SDL_Renderer* r, int* w, int* h);
  ~Player();
  
  void setPos(vec2 p);
  void setRot(float r);

  void setScene(Scene* s);
  void setCanvas(Canvas* c);
  vec2 getPos();
  float getRot();

  void update(double deltaTime);
  void keyPressed(SDL_Scancode key);
  void keyReleased(SDL_Scancode key);
  void interact(InteractionID ID);
  void draw();
};

#endif
