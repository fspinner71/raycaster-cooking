#include "canvas.h"
#include <SDL3_ttf/SDL_ttf.h>

Canvas::Canvas(SDL_Renderer* r, int* w, int* h)
{
  renderer = r;
  width = w;
  height = h;

  textBox = new Frame(renderer);
  showTextBox = false;
  
  SDL_FRect textRect;
  textRect.x = TEXT_BOX_PADDING;
  textRect.y = *height - TEXT_BOX_HEIGHT - TEXT_BOX_PADDING;
  textRect.w = *width - 2*TEXT_BOX_PADDING;
  textRect.h = TEXT_BOX_HEIGHT;

  textBox->setRect(textRect);
  textBox->setColor({TEXT_BOX_COLOR});
  text = new Text(renderer, "ComicSans", "");

  textRect.x += TEXT_BOX_TEXT_PADDING;
  textRect.y += TEXT_BOX_TEXT_PADDING;
  textRect.w -= 2 * TEXT_BOX_TEXT_PADDING;
  textRect.h -= 2 * TEXT_BOX_TEXT_PADDING;

  text->setColor({TEXT_BOX_TEXT_COLOR});
  text->setRect(textRect);

  crossHairTex = AssetManager::getInstance().getTextureID("crosshair");
  SDL_Texture* t = AssetManager::getInstance().getTexture(crossHairTex);
  crossHairRect.x = *width/2 - t->w/2;
  crossHairRect.y = *height/2 - t->h/2;
  crossHairRect.w = t->w;
  crossHairRect.h = t->h;
}

void Canvas::enableTextBox()
{
  showTextBox = true;
}
void Canvas::disableTextBox()
{
  showTextBox = false;
}
void Canvas::setTextBoxText(std::string s)
{
  text->setText(s);
}

void Canvas::draw()
{
  SDL_FRect src = {0, 0, crossHairRect.w, crossHairRect.h};
  SDL_RenderTexture(
    renderer,
    AssetManager::getInstance().getTexture(crossHairTex),
    &src,
    &crossHairRect
  );
  if(showTextBox)
  {
    textBox->draw();
    text->draw();
  }
}

Canvas::~Canvas()
{
  if(text)
  {
    text->free();
    delete text;
    text = NULL;
  }
  if(textBox)
  {
    delete textBox;
    textBox = NULL;
  }
}
