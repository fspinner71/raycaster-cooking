#include "frame.h"

Frame::Frame(SDL_Renderer* r)
{
  renderer = r;
}

void Frame::setColor(vec4 c)
{
  clr = c;
}
void Frame::setRect(SDL_FRect r)
{
  rect = r;
}
void Frame::draw()
{
  SDL_SetRenderDrawColor(renderer, clr.x, clr.y, clr.z, clr.w);
  SDL_RenderFillRect(renderer, &rect);
}
