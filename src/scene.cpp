#include "scene.h"

Scene::Scene()
{
  
}

void Scene::addNPC(NPC* n)
{
  npcs.push_back(n);
}

void Scene::setSkyBox(SDL_Texture* s)
{
  skyBox = s;
}
std::vector<NPC*> Scene::getNPCs()
{
  return npcs;
}
SDL_Texture* Scene::getSkyBox()
{
  return skyBox;
}

Map* Scene::getMap()
{
  return map;
}

void Scene::update(double deltaTime)
{
  for(int i = 0; i < npcs.size(); i++)
  {
    npcs.at(i)->update(deltaTime);
  }
}

Scene::~Scene()
{
  for(int i = 0; i < npcs.size(); i++)
  {
    npcs.at(i)->free();
    delete npcs.at(i);
  }
  if(map)
  {
    map->free();
    delete map;
    map = NULL;
  }
}
