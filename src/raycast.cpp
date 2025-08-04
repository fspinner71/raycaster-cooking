#include "raycast.h"

void Raycast::setPos(vec2 p)
{
  pos = p;
}
void Raycast::setDir(vec2 d)
{
  dir = d.unit();
}
vec2 Raycast::getPos()
{
  return pos;
}
vec2 Raycast::getDir()
{
  return dir;
}

void Raycast::addResult(std::vector<RaycastResult>* vector, bool hit, int hitID, int index, int side, vec2 sideDist, vec2 deltaDist, vec2i mapCoords)
{
  RaycastResult result = {};
  result.index = index;
  result.hitID = hitID;
  result.side = side;

  result.hit = hit;
  if(result.hit)
  {
    if(side == 0)
    {
      result.perpWallDist = (sideDist.x - deltaDist.x);
      result.wallX = pos.y + result.perpWallDist * dir.y;
      result.wallX -= std::floor(result.wallX);
      result.hitPos = {(float)mapCoords.x, (float)mapCoords.y + result.wallX};
      if((int)pos.x > mapCoords.x)
      {
        result.hitPos.x += 1;
      }
    } else {

      result.perpWallDist = (sideDist.y - deltaDist.y);
      result.wallX = pos.x + result.perpWallDist * dir.x;
      result.wallX -= std::floor(result.wallX);
      result.hitPos = {(float)mapCoords.x + result.wallX, (float)mapCoords.y};
      if((int)pos.y > mapCoords.y)
      {
        result.hitPos.y += 1;
      }
    }
    result.dist = std::sqrt(std::pow(result.hitPos.x - pos.x, 2) + std::pow(result.hitPos.y - pos.y, 2));
    vector->push_back(result);

 } else {
    result.hitPos = {pos.x + dir.x, pos.y + dir.y};
    result.hitNormal = {0.f, 0.f};
    result.hitID = -1;
    result.perpWallDist = 0;
  }

}

void Raycast::cast(Map* m, std::vector<RaycastResult>* vector, int index)
{
  if(pos.x >= m->getWidth() || pos.x < 0 || pos.y >= m->getHeight() || pos.y < 0)
  {
    return;
  }
  vec2i mapCoords = {(int)pos.x, (int)pos.y};

  vec2 deltaDist;
  deltaDist.x = (dir.x == 0) ? 1e30 : std::abs(1 / dir.x);
  deltaDist.y = (dir.y == 0) ? 1e30 : std::abs(1 / dir.y);

  vec2 sideDist;
  vec2i step;
  if(dir.x < 0)
  {
    step.x = -1;
    sideDist.x = (pos.x - mapCoords.x) * deltaDist.x;
  } else {
    step.x = 1;
    sideDist.x = (mapCoords.x + 1.f - pos.x) * deltaDist.x;
  }
  if(dir.y < 0)
  {
    step.y = -1;
    sideDist.y = (pos.y - mapCoords.y) * deltaDist.y;
  } else {
    step.y = 1;
    sideDist.y = (mapCoords.y + 1.f - pos.y) * deltaDist.y;
  }
  
  int s = 0;
  bool hit = false;

  while(!hit)
  {
    if(sideDist.x < sideDist.y)
    {
      sideDist.x += deltaDist.x;
      mapCoords.x += step.x;
      s = 0;
    } else {
      sideDist.y += deltaDist.y;
      mapCoords.y += step.y;
      s = 1;
    }
    if(mapCoords.x >= m->getWidth() || mapCoords.x < 0 || mapCoords.y >= m->getHeight() || mapCoords.y < 0)
    {
      break;
    }

    int tile = m->getTile(mapCoords.x, mapCoords.y);
    if(tile != -1)
    {
      addResult(vector, true, tile, index, s, sideDist, deltaDist, mapCoords);
      if(tile != 2 && tile != 3)
      {
        hit = true;
      }
    }
  }


}
