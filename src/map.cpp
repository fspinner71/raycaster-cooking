#include "map.h"


Map::Map()
{
  width = MAP_DEFAULT_W;
  height = MAP_DEFAULT_H;
  map = new int*[MAP_DEFAULT_H];
  for(int r = 0; r < MAP_DEFAULT_H; r++)
  {
    map[r] = new int[MAP_DEFAULT_W];
    for(int c = 0; c < MAP_DEFAULT_W; c++)
    {
      map[r][c] = 0;
    }
  }
} 

int Map::getWidth()
{
  return width;
}
int Map::getHeight()
{
  return height;
}
int Map::getTile(int c, int r)
{
  return map[r][c];
}

void Map::free()
{
  for(int r = 0; r < height; r++)
  {
    delete[] map[r];
  }
  delete[] map;
}
