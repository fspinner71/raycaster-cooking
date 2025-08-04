#include "game.h"
#include "fridge.h"


int Game::status = INIT_FAILURE;
Game* Game::instance = NULL;

bool Game::initSDL()
{
  if(!SDL_Init(SDL_FLAGS))
  {
    std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
    return false;
  }
  if(!TTF_Init())
  {
    std::cout << "Could not initialize TTF: " << SDL_GetError();
  }
  
  window = SDL_CreateWindow("Tetris", WIDTH, HEIGHT, WINDOW_FLAGS);
  if(!window)
  {
    std::cout << "Could not create window: " << SDL_GetError() << std::endl;
    return false;
  }
  
  renderer = SDL_CreateRenderer(window, NULL);
  if(!renderer)
  {
    std::cout << "Could not create renderer: " << SDL_GetError() << std::endl;
    return false;
  }
  
 

  return true;
}

bool Game::loadMedia()
{
  if(!Strip::loadWallTexture(renderer))
  {
    return false;
  }

  skyBox = IMG_LoadTexture(renderer, "assets/images/skybox.png");
  if(!skyBox)
  {
    std::cout << "Could not load sky box texture: " << SDL_GetError() << std::endl;
    return false;
  }
  if(!SDL_SetTextureScaleMode(skyBox, SDL_SCALEMODE_NEAREST))
  {
    std::cout << "Could not set sky box texture scalemode: " << SDL_GetError() << std::endl;
    return false;
  }
  Text::loadFonts(renderer);
  Stove::loadTexture(renderer);
  Fridge::loadTexture(renderer);

  AssetManager::getInstance();

  return true;
}

Game::Game()
{
  if(!initSDL())
  {
    status = INIT_FAILURE;
    return;
  }
  if(!loadMedia())
  {
    status = INIT_FAILURE;
    return;
  }
  width = WIDTH;
  height = HEIGHT;

  event = new SDL_Event;

  isRunning = false; 

  canvas = new Canvas(renderer, &width, &height);
  
  int m[MAP_DEFAULT_H][MAP_DEFAULT_W] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, -1, -1, -1, 0, 0, 0, 0, 0, 1},
    {0, -1, -1, -1, -1, -1, 0, -1, -1, 1},
    {0, -1, -1, -1, -1, -1, 0, -1, -1, 1},
    {1, -1, -1, -1, -1, -1, 0, -1, -1, 1},
    {1, -1, -1, -1, -1, -1, 0, -1, -1, 1},
    {1, -1, -1, 2, -1, -1, -1, -1, -1, 1},
    {1, -1, -1, -1, -1, -1, -1, -1, -1, 1},
    {1, -1, -1, -1, -1, -1, -1, -1, -1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  scene = new Scene();
  scene->setMap(m);

  scene->setSkyBox(skyBox);
  
  Stove* stove = new Stove(renderer);
  stove->setPos({1.5, 1.5});
  
  Fridge* fridge = new Fridge(renderer, Item::RawPatty);
  fridge->setPos({2.5, 1.5});


  scene->addNPC(stove);
  scene->addNPC(fridge);

  plr = new Player(renderer, &width, &height);
  plr->setScene(scene);
  plr->setCanvas(canvas);
  plr->setPos(vec2{1, 4});

  cam = new Camera(renderer, &width, &height);
  cam->setScene(scene);
  
  Game::status = INIT_SUCCESS;
  Game::instance = this;
}

void Game::pollEvents()
{
  while(SDL_PollEvent(event))
  {
    switch(event->type)
    {
    case SDL_EVENT_QUIT:
      isRunning = false;
      break;
    case SDL_EVENT_KEY_DOWN:
      plr->keyPressed(event->key.scancode);
      switch(event->key.scancode)
      {
        case SDL_SCANCODE_ESCAPE:
          isRunning = false;
          break;
        default:
          break;
      }
      break;
    case SDL_EVENT_KEY_UP:
      plr->keyReleased(event->key.scancode);
      break;
    default:
      break;
    }
  }
}

void Game::update(double deltaTime)
{
  scene->update(deltaTime);
  plr->update(deltaTime);
  cam->setPos(plr->getPos());
  cam->setRot(plr->getRot());
  cam->update(deltaTime);
}

void Game::draw()
{
  SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

  SDL_RenderClear(renderer);
  
  cam->drawView();

  plr->draw();

  canvas->draw();

  SDL_RenderPresent(renderer);
}

bool Game::run()
{
  isRunning = true;
  
  Uint64 now = SDL_GetPerformanceCounter();
  Uint64 last = 0;
  double deltaTime = 0;

  while(isRunning)
  {
    last = now;
    now = SDL_GetPerformanceCounter();
    deltaTime = (double)((now - last) * 1000 / (double)SDL_GetPerformanceFrequency()) * 0.001;
  

    pollEvents();

    update(deltaTime);

    draw();

    SDL_Delay(16);
  }

  return true;
}

Game::~Game()
{
  Strip::free();
  if(skyBox)
  {
    SDL_DestroyTexture(skyBox);
    skyBox = NULL;
  } 
  if(cam)
  {
    delete cam;
    cam = NULL;
  }
  if(plr)
  {
    delete plr;
    plr = NULL;
  }
  if(scene)
  {
    delete scene;
    scene = NULL;
  }
  if(canvas)
  {
    delete canvas;
    canvas = NULL;
  }
  Fridge::free();
  Stove::free();
  Text::freeFonts();
  if(event != NULL)
  {
    delete event;
    event = NULL;
  }
  if(renderer)
  {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }
  if(window)
  {
    SDL_DestroyWindow(window);
    window = NULL;
  }

  SDL_Quit();
  TTF_Quit();

}

Game* Game::getInstance()
{
  return instance;
}

int Game::getStatus()
{
  return status;
}
