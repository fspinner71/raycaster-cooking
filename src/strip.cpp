#include "strip.h"

SDL_Renderer* Strip::renderer = NULL;
SDL_Texture* Strip::wallTex = NULL;

bool Strip::loadWallTexture(SDL_Renderer* r)
{
  renderer = r;
  wallTex = IMG_LoadTexture(renderer, WALL_TEX_PATH);
  if(!wallTex)
  {
    std::cout << "Could not load wall texture: " << SDL_GetError() << std::endl;
    return false;
  }
  if(!SDL_SetTextureScaleMode(wallTex, SDL_SCALEMODE_NEAREST))
  {
    std::cout << "Could not set wall texture scale mode: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

void Strip::free()
{
  if(wallTex)
  {
    SDL_DestroyTexture(wallTex);
    wallTex = NULL;
  }
}

Strip::Strip()
{
  enabled = false;
}

Strip::Strip(RaycastResult ray, vec2 pos, float rot, int screenWidth, int screenHeight, int quality, int fov)
{
  drawRect.x = (float)ray.index * screenWidth/quality;
  drawRect.w = (float)screenWidth/quality;

  srcRect.y = 0;
  srcRect.h = WALL_TEX_SIZE;
  if(ray.hit)
  {
    height = (WALL_HEIGHT/ray.perpWallDist);
    dist = ray.dist;
      
    drawRect.y = (float)screenHeight/2 - height/2;
    drawRect.h = height;

    srcRect.x = WALL_TEX_SIZE * (ray.hitID + ray.wallX);
    srcRect.w = 64;
  
    float l = std::sqrt(std::pow(ray.hitPos.x - pos.x, 2) + std::pow(ray.hitPos.y - pos.y, 2));
    float a = rad((float)fov)/quality;

    if(ray.index > quality/2)
    {
      srcRect.w = std::abs((l * std::sin(a))/std::sin(PI/2 + rot + a * ((float)quality/2 - ray.index)));
    } else {
      srcRect.w = std::abs((l * std::sin(a))/std::sin(PI/2 + rot + a * (ray.index - (float)quality/2)));
    }
  }
}

float Strip::getHeight()
{
  return height;
}

float Strip::getDist()
{
  return dist;
}

bool Strip::isEnabled()
{
  return enabled;
}

void Strip::draw()
{
  SDL_RenderTexture(
    renderer,
    wallTex,
    &srcRect,
    &drawRect
  );
}
