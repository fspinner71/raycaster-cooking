#include "text.h"

Text::Text(SDL_Renderer* r, int f, std::string t)
{
  renderer = r;
  font = f;
  setText(t);
}
Text::Text(SDL_Renderer* r, std::string fontName, std::string t)
{
  renderer = r;
  font = AssetManager::getInstance().getFontID(fontName);
  setText(t);
}
void Text::setFont(int ID)
{
  font = ID;
}
void Text::setFont(std::string name)
{
  font = AssetManager::getInstance().getFontID(name);
}
void Text::setText(std::string t)
{
  text = t;
  if(text.length() <= 0 || text.at(text.length() - 1) != ' ')
  {
    text += " ";
  }
}
void Text::setRect(SDL_FRect r)
{
  rect = r;
}
void Text::setColor(vec3 c)
{
  clr = c;
}

void Text::draw()
{
  Font f = AssetManager::getInstance().getFont(font);
  if(text.length() <= 1)
  {
    return;
  }
  SDL_SetTextureColorMod(f.tex, clr.x, clr.y, clr.z);

  int totalWidth = 0;
  int line = 0;
  int nextWord = 0;
  int pos = 0;

  SDL_FRect drawRect;

  nextWord = text.find(" ", nextWord);

  while(nextWord != std::string::npos) 
  {
    int currentWidth;
    TTF_GetStringSize(f.font, text.substr(pos, nextWord + 1 - pos).c_str(), 0, &currentWidth, NULL);
    
    if(totalWidth + currentWidth > rect.w)
    {
      line += f.tex->h;
      totalWidth = 0;
      pos++;
    }

    int wordWidth = 0;
    for(int i = pos; i < nextWord; i++)
    {
      SDL_FRect glyphRect = f.glyphs[text.at(i)];
      drawRect.x = rect.x + totalWidth + wordWidth;
      drawRect.y = rect.y + line;
      drawRect.w = glyphRect.w;
      drawRect.h = glyphRect.h; 

      SDL_RenderTexture(renderer, f.tex, &glyphRect, &drawRect);

      wordWidth += drawRect.w;
    }
    

    totalWidth += wordWidth;

    pos = nextWord;
    nextWord = text.find(" ", nextWord + 1);
  }
}

void Text::free()
{
  
}
