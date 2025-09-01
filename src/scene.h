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
  int skyBox;
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
  void setSkyBox(int tex);
  std::vector<NPC*> getNPCs();
  int getSkyBox();
  Map* getMap();

  void update(double deltaTime);
};

#endif
