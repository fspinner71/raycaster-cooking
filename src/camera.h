#ifndef CAMERA_H
#define CAMERA_H

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <vector>
#include "math.h"
#include "map.h"
#include "raycast.h"
#include "strip.h"
#include "scene.h"
#include <math.h>


#define CAMERA_FOV 90
#define CAMERA_QUALITY 300



#define FLOOR_COLOR 225, 225, 175, 255
#define CEILING_COLOR 50, 50, 50, 255

class Camera
{
private:
  SDL_Renderer* renderer;
  Scene* scene;
  vec2 pos;
  float rot;
  vec2 lookDir;

  int* width;
  int* height;

  Raycast rays[CAMERA_QUALITY];
  std::vector<Strip>* strips;
  std::vector<RaycastResult>* rayResults;

public:
  Camera(SDL_Renderer* r, int* w, int* h);
  ~Camera();

  void setScene(Scene* s);
  
  void setPos(vec2 p);
  void setRot(float r);

  void drawView();
  void update(double deltaTime);
};

#endif
