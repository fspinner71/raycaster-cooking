#include "camera.h"

Camera::Camera(SDL_Renderer* r, int* w, int* h)
{
  renderer = r;
  pos = {0.f, 0.f};
  rot = 0.f;
  lookDir = {std::cos(rot), std::sin(rot)};

  width = w;
  height = h; 

  rayResults = new std::vector<RaycastResult>;
  strips = new std::vector<Strip>;

  rayResults->reserve(CAMERA_QUALITY * 2);
  strips->reserve(CAMERA_QUALITY * 2);
}

void Camera::setScene(Scene* s)
{
  scene = s;
}

void Camera::setPos(vec2 p)
{
  pos = p;
}
void Camera::setRot(float r)
{
  rot = r;
  lookDir = {std::cos(rot), std::sin(rot)};
}

void Camera::update(double deltaTime)
{
  strips->clear();
  rayResults->clear();

  float rayRot = rot - rad((float)CAMERA_FOV/2);
  for(int i = 0; i < CAMERA_QUALITY; i++)
  {
    rays[i].setPos(pos);
    rays[i].setDir({std::cos(rayRot), std::sin(rayRot)});
    rays[i].cast(scene->getMap(), rayResults, i);
    
    rayRot += rad((float)CAMERA_FOV)/(float)CAMERA_QUALITY; 
  }
  for(int i = 0; i < rayResults->size(); i++)
  {
    Strip strip = Strip(renderer, rayResults->at(i), pos, rot, *width, *height, CAMERA_QUALITY, CAMERA_FOV);

    int j = 0;
    while(j < strips->size())
    {
      if(strips->at(j).getHeight() >= strip.getHeight())
      {
        break;
      }
      j++;
    }
    strips->insert(strips->begin() + j, strip);
  }

}

void Camera::drawView()
{
  int sbID = scene->getSkyBox();
  SDL_Texture* skyBox = AssetManager::getInstance().getTexture(sbID);
  SDL_FRect skySrc;
  skySrc.h = skyBox->h;
  skySrc.w = skyBox->w * (float)CAMERA_FOV/360;
  skySrc.y = 0;
  skySrc.x = (skyBox->w - skySrc.w) * (rot - rad(CAMERA_FOV)/2)/(2*PI);

  SDL_FRect skyDraw;
  skyDraw.x = 0;
  skyDraw.y = 0;
  skyDraw.w = *width;
  skyDraw.h = *height;

  if(skySrc.x < 0)
  {
    SDL_FRect nSkyDraw = skyDraw;
    nSkyDraw.w *= -skySrc.x/skySrc.w;
    skyDraw.x = nSkyDraw.w;
    skyDraw.w -= nSkyDraw.w;

    SDL_FRect nSkySrc = skySrc;
    nSkySrc.x = skyBox->w + skySrc.x;
    nSkySrc.w = -skySrc.x;
    skySrc.w += skySrc.x;
    skySrc.x = 0;

    SDL_RenderTexture(renderer, skyBox, &nSkySrc, &nSkyDraw);
  }


  SDL_RenderTexture(renderer, skyBox, &skySrc, &skyDraw);

  SDL_FRect floorRect;
  floorRect.x = 0;
  floorRect.w = *width;
  floorRect.h = (float)*height/2;
  floorRect.y = (float)*height/2;

  SDL_SetRenderDrawColor(renderer, FLOOR_COLOR);
  SDL_RenderFillRect(renderer, &floorRect);

   //SORT NPCS BY DISTANCE
  std::vector<NPC*> npcs = scene->getNPCs();
  int furthest = -1;
  float furthestDistance = 0.f;
  for(int i = 0; i < npcs.size(); i++)
  {
    furthest = i;
    furthestDistance = npcs.at(furthest)->getDist(pos);
    for(int j = i + 1; j < npcs.size(); j++)
    {
      float curr = npcs.at(j)->getDist(pos);
      if(curr > furthestDistance)
      {
        furthest = j;
        furthestDistance = curr;
      }
    }

    if(furthest != i)
    {
      NPC* temp = npcs.at(i);
      npcs[i] = npcs.at(furthest);
      npcs[furthest] = temp;
    }
  }
  
  int j = 0;
  for(int i = 0; i < strips->size(); i++)
  {
    Strip s = strips->at(i);
    if(j < npcs.size())
    {
      NPC* n = npcs.at(j);
      if(s.getDist() < n->getDist(pos))
      {
        j++;
        n->draw(*width, *height, pos, rot, rad(CAMERA_FOV));
      }
    } 
    s.draw();
  } 
  if(j < npcs.size())
  {
    for(int i = j; i < npcs.size(); i++)
    {
      npcs.at(i)->draw(*width, *height, pos, rot, rad(CAMERA_FOV));
    }
  }
}

Camera::~Camera()
{
  rayResults->clear();
  delete rayResults;
  rayResults = NULL;
  
  strips->clear();
  delete strips;
  strips = NULL;
}
