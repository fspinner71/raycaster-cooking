#include "player.h"
#include <SDL3/SDL_render.h>

Player::Player(SDL_Renderer* r, int* w, int* h) : interaction(InteractionID::None)
{
  renderer = r;
  keystates = SDL_GetKeyboardState(NULL);
  pos = {0.f, 0.f}; 
  lookDir = {0.f, 0.f};
  rot = 0.f;
  rVel = 0.f;
  speed = PLAYER_SPEED;
  rSpeed = PLAYER_SENSITIVITY;
  width = w;
  height = h;
  timeWalking = 0.f;
  holding = Item::None;

  itemTextures[(int)Item::RawPatty] = IMG_LoadTexture(renderer, "assets/images/rawpatty.png");
  itemTextures[(int)Item::CookedPatty] = IMG_LoadTexture(renderer, "assets/images/cookedpatty.png");
  itemTextures[(int)Item::Bun] = IMG_LoadTexture(renderer, "assets/images/bun.png");
  itemTextures[(int)Item::LettuceSlice] = IMG_LoadTexture(renderer, "assets/images/lettuce.png");
  itemTextures[(int)Item::TomatoSlice] = IMG_LoadTexture(renderer, "assets/images/tomato.png");
  itemTextures[(int)Item::Cheese] = IMG_LoadTexture(renderer, "assets/images/cheese.png");
  itemTextures[(int)Item::Plate] = IMG_LoadTexture(renderer, "assets/images/plate.png");

  for(int i = 0; i < (int)Item::Count; i++)
  {
    SDL_SetTextureScaleMode(itemTextures[i], SDL_SCALEMODE_NEAREST);
  }

  interaction = Interaction(InteractionID::None);

  drawRect.w = PLAYER_RECT_W;
  drawRect.h = PLAYER_RECT_H;

  states[(int)States::Interacting] = false;
}
void Player::setScene(Scene* s)
{
  scene = s;
}
void Player::setCanvas(Canvas* c)
{
  canvas = c;
}
vec2 Player::getPos()
{
  return pos;
}
float Player::getRot()
{
  return rot;
}
void Player::setPos(vec2 p)
{
  pos = p;
}
void Player::setRot(float r)
{
  rot = r;
  lookDir.x = std::cos(rot);
  lookDir.y = std::sin(rot);
}

void Player::keyPressed(SDL_Scancode key)
{
  switch(key)
  {
  case SDL_SCANCODE_F:
    if(currentInteract)
    {
      interact(currentInteract->getInteractionID());
    }
    break;
  case SDL_SCANCODE_RETURN:
    if(states[(int)States::Interacting])
    {
      interaction.next();
    }
    break;
  default:
    break;
  }
}

void Player::keyReleased(SDL_Scancode key)
{
  switch(key)
  {
  default:
    break;
  }
}

void Player::interact(InteractionID ID)
{
  states[(int)States::Interacting] = true;
  interaction = Interaction(ID);

  canvas->enableTextBox(); 

  currentInteract->interact(&holding);
}

void Player::update(double deltaTime)
{
  vec2 dir = {0.f, 0.f};

  vel.x = 0;
  vel.y = 0;

  if(!states[(int)States::Interacting])
  {
    if(keystates[SDL_SCANCODE_W])
    {
      dir.y += 1.f;
    }
    if(keystates[SDL_SCANCODE_S])
    {
      dir.y -= 1.f;
    }
    if(keystates[SDL_SCANCODE_A])
    {
      dir.x -= 1.f;
    }
    if(keystates[SDL_SCANCODE_D])
    {
      dir.x += 1.f;
    }

    dir = {lookDir.x * dir.y - lookDir.y * dir.x, lookDir.y * dir.y + lookDir.x * dir.x};
    dir = dir.unit();

    float rDir = 0.f;

    if(keystates[SDL_SCANCODE_Q])
    {
      rDir -= 1.f;
    }
    if(keystates[SDL_SCANCODE_E])
    {
      rDir += 1.f;
    }

    vel.x = dir.x * speed;
    vel.y = dir.y * speed;

    rVel = rDir * rSpeed;

  }
  
  if(scene->getMap()->getTile((int)(pos.x + vel.x * deltaTime), (int)pos.y) != -1)
  {
    vel.x = 0;
  }
  if(scene->getMap()->getTile((int)pos.x, (int)(pos.y + vel.y * deltaTime)) != -1)
  {
    vel.y = 0;
  }

  states[(int)States::Walking] = vel.magnitude() > 0.001f;

  if(states[(int)States::Walking])
  {
    timeWalking += deltaTime;
  } else {
    timeWalking = 0.f;
  }

  pos.x += vel.x * deltaTime;
  pos.y += vel.y * deltaTime;

  rot += rVel * deltaTime;
  rot = std::fmod(rot, 2*PI);

  lookDir.x = std::cos(rot);
  lookDir.y = std::sin(rot);

  if(states[(int)States::Interacting])
  {
    interaction.update(deltaTime);
    canvas->setTextBoxText(interaction.getCurrentText());
    if(interaction.finished())
    {
      states[(int)States::Interacting] = false;
      canvas->disableTextBox();
    }
  }

  std::vector<NPC*> npcs = scene->getNPCs();
  bool NPCFound = false;
  for(int i = 0; i < npcs.size(); i++)
  {
    vec2 npcPos = npcs.at(i)->getPos();

    float angle = std::atan2(npcPos.y - pos.y, npcPos.x - pos.x);
    float diff = angle - rot;

    if(diff < -PI)
    {
      diff = diff + 2*PI;
    } else if(diff > PI)
    {
      diff = diff - 2*PI;
    }

    float a = rad(PLAYER_INTERACT_ANGLE);
    float t = 1 - (a/2 - diff)/a;

    float dist = npcs.at(i)->getDist(pos);

    if(dist < PLAYER_INTERACT_DISTANCE && t > 0 && t < 1)
    {
      currentInteract = npcs.at(i);
      NPCFound = true;
      break;
    }
  }
  if(!NPCFound)
  {
    currentInteract = NULL;
  }
}

void Player::draw()
{
  if(holding == Item::None)
  {
    return;
  }

  SDL_Texture* tex = itemTextures[(int)holding];
  SDL_FRect srcRect;
  srcRect.x = srcRect.y = 0;
  srcRect.w = tex->w;
  srcRect.h = tex->h;

  SDL_FRect drawRect;
  drawRect.w = srcRect.w * HOLDING_ITEM_SCALE;
  drawRect.h = srcRect.h * HOLDING_ITEM_SCALE;
  drawRect.x = *width - drawRect.w + HOLDING_ITEM_OFFSET_X;
  drawRect.y = *height - drawRect.h + HOLDING_ITEM_OFFSET_Y;

  drawRect.x += HOLDING_WALK_AMPLITUDE_X * std::sin(HOLDING_WALK_FREQUENCY * timeWalking);
  drawRect.y -= HOLDING_WALK_AMPLITUDE_Y * std::abs(std::cos(HOLDING_WALK_FREQUENCY * timeWalking));

  SDL_RenderTexture(renderer, tex, &srcRect, &drawRect);
}

Player::~Player()
{
  for(int i = 0; i < (int)Item::Count; i++)
  {
    SDL_DestroyTexture(itemTextures[i]);
  }
}
