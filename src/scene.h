#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "map.h"
#include "npc.h"
#include "stove.h"
#include "fridge.h"

class Scene
{
private:
  Map* map;
  SDL_Texture* skyBox;
  std::vector<NPC*> npcs;
public:
  Scene();
  ~Scene();
  
  template <size_t w, size_t h>
  void setMap(int (&m)[h][w])
  {
    map = new Map(m);  
  }

  void addNPC(NPC* n);
  void setSkyBox(SDL_Texture* s);
  std::vector<NPC*> getNPCs();
  SDL_Texture* getSkyBox();
  Map* getMap();

  void update(double deltaTime);
};

#endif
