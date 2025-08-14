#ifndef GUI_H
#define GUI_H

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_textengine.h>
#include <vector>
#include <string>
#include "frame.h"
#include "text.h"

#define TEXT_BOX_PADDING 20
#define TEXT_BOX_HEIGHT 400
#define TEXT_BOX_COLOR 52, 52, 52, 100
#define TEXT_BOX_FONT_SIZE 30

#define TEXT_BOX_TEXT_PADDING 5
#define TEXT_BOX_TEXT_COLOR 255, 255, 255

class Canvas
{
private:
  SDL_Renderer* renderer;

  int* width;
  int* height;

  Frame* textBox;
  Text* text;
  bool showTextBox;
public:
  Canvas(SDL_Renderer* r, int* w, int* h);
  ~Canvas();

  void enableTextBox();
  void disableTextBox();
  void setTextBoxText(std::string s);
  void draw();
};

#endif
