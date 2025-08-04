#include "sprite.h"


Sprite::Sprite(SDL_Renderer* r, SDL_Texture* t)
{
  renderer = r;
  tex = t;
  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = tex->w;
  srcRect.h = tex->h;
  size.x = tex->w;
  size.y = tex->h;
  frameWidth = tex->w;
  frameIndex = 0;
  zOffset = 0;
}

void Sprite::setPos(vec2 p)
{
  pos = p;
}

void Sprite::setSize(vec2 s)
{
  size = s;
}

void Sprite::setZOffset(float z)
{
  zOffset = z;
}

void Sprite::setFrameWidth(int w)
{
  frameWidth = w;
  srcRect.x = frameIndex * frameWidth;
  srcRect.w = frameWidth;
}
void Sprite::setFrameIndex(int i)
{
  frameIndex = i;
  srcRect.x = frameIndex * frameWidth;
}

vec2 Sprite::getPos()
{
  return pos;
}

float Sprite::getDist(vec2 p)
{
  return std::sqrt(std::pow(pos.x - p.x, 2) + std::pow(pos.y - p.y, 2));
}

void Sprite::setSrcRect(SDL_FRect r)
{
  srcRect = r;
}

void Sprite::setTexture(SDL_Texture* t)
{
  tex = t;
}

void Sprite::update(double deltaTime)
{

}

void Sprite::draw(int screenWidth, int screenHeight, vec2 camPos, float camRot, float fov)
{
  float angle = std::atan2(pos.y - camPos.y, pos.x - camPos.x);
  float diff = angle - camRot;

  if(diff < -PI)
  {
    diff = diff + 2*PI;
  } else if(diff > PI)
  {
    diff = diff - 2*PI;
  }

  float t = 1 - (fov/2 - diff)/fov;

  if(t < 0 || t > 1)
  {
    return;
  }

  float screenX = screenWidth * t;

  float dist = getDist(camPos);

  float scale = 1/dist;

  drawRect.x = screenX - size.x * 0.5 * scale;
  drawRect.y = (float)screenHeight/2 - size.y * 0.5 * scale - zOffset * scale;
  drawRect.w = size.x * scale;
  drawRect.h = size.y * scale;

  SDL_RenderTexture(
    renderer,
    tex,
    &srcRect,
    &drawRect
  );
}

void Sprite::free()
{

}
