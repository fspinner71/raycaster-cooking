#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_timer.h>
#include <SDL3_ttf/SDL_textengine.h>
#include "assetmanager.h"
#include "map.h"
#include "player.h"
#include "camera.h"
#include "strip.h"
#include "scene.h"
#include "canvas.h"

#define SDL_FLAGS SDL_INIT_VIDEO

#define WINDOW_FLAGS 0
#define WIDTH 1920
#define HEIGHT 1080

#define INIT_SUCCESS 1
#define INIT_FAILURE 0

class Game
{
private:
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Event* event;

  int width;
  int height;

  Scene* scene;
  Player* plr;
  Camera* cam;
  Canvas* canvas;

  SDL_Texture* skyBox;

  bool isRunning;

  bool initSDL();
  bool loadMedia();
  void pollEvents();
  void update(double deltaTime);
  void draw();

  static Game* instance;
  static int status;
public:
  Game();
  ~Game();
  bool run(); 

  Game* getInstance();
  int getStatus();
};

#endif
