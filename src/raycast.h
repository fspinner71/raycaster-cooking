#ifndef RAYCAST_H
#define RAYCAST_H

#include <vector>
#include "math.h"
#include "map.h"

struct RaycastResult
{
  bool hit;
  vec2 pos, hitPos;
  vec2 hitNormal;
  int hitID;
  float perpWallDist;
  float wallX;
  int side;
  float dist;
  int index;
};

class Raycast
{
private:
  vec2 pos;
  vec2 dir;

  void addResult(std::vector<RaycastResult>* vector, bool hit, int hitID, int index, int side, vec2 sideDist, vec2 deltaDist, vec2i mapCoords);
public:
  void setPos(vec2 p);
  void setDir(vec2 d);
  vec2 getDir();
  vec2 getPos();

  void cast(Map* m, std::vector<RaycastResult>* vector, int index);
};

#endif
