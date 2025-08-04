#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <SDL3/SDL.h>

#define MAP_DEFAULT_W 10
#define MAP_DEFAULT_H 10

#define MAP_UNIT_W 60
#define MAP_UNIT_H 60

#define MAP_COLOR_0 0, 0, 0, 255
#define MAP_COLOR_1 0, 0, 255, 255

class Map
{
private:

  int width;
  int height;
  int** map;
public:
  template <size_t w, size_t h>
  Map(int (&m)[h][w])
  {
    width = w;
    height = h;
    map = new int*[height];
    for(int r = 0; r < height; r++)
    {
      map[r] = new int[width];
      for(int c = 0; c < width; c++)
      {
        map[r][c] = m[r][c];
      }
    }
  }
  Map();


  int getWidth();
  int getHeight();

  int getTile(int c, int r);

  void free();

};

#endif
