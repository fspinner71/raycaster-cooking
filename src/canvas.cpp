#include "canvas.h"
#include <SDL3_ttf/SDL_ttf.h>

Canvas::Canvas(SDL_Renderer* r, int* w, int* h)
{
  renderer = r;
  width = w;
  height = h;

  textEngine = TTF_CreateRendererTextEngine(renderer);
  font = TTF_OpenFont("assets/fonts/ComicSansMS.ttf", TEXT_BOX_FONT_SIZE);

  textBox = new Frame(renderer);
  showTextBox = false;
  
  SDL_FRect textRect;
  textRect.x = TEXT_BOX_PADDING;
  textRect.y = *height - TEXT_BOX_HEIGHT - TEXT_BOX_PADDING;
  textRect.w = *width - 2*TEXT_BOX_PADDING;
  textRect.h = TEXT_BOX_HEIGHT;

  textBox->setRect(textRect);
  textBox->setColor({TEXT_BOX_COLOR});
  text = new Text(renderer, COMIC_SANS, "");

  textRect.x += TEXT_BOX_TEXT_PADDING;
  textRect.y += TEXT_BOX_TEXT_PADDING;
  textRect.w -= 2 * TEXT_BOX_TEXT_PADDING;
  textRect.h -= 2 * TEXT_BOX_TEXT_PADDING;

  text->setColor({TEXT_BOX_TEXT_COLOR});
  text->setRect(textRect);
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
  if(font)
  {
    TTF_CloseFont(font);
    font = NULL;
  }
  if(textBox)
  {
    delete textBox;
    textBox = NULL;
  }
  if(textEngine)
  {
    TTF_DestroyRendererTextEngine(textEngine);
    textEngine = NULL;
  }
}
