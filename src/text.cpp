#include "text.h"

TTF_Font* Text::fonts[NUM_FONTS];
SDL_Texture* Text::fontTextures[NUM_FONTS];
SDL_FRect Text::glyphs[NUM_FONTS][NUM_CHARS];

void Text::loadFonts(SDL_Renderer* renderer)
{
  fonts[COMIC_SANS] = TTF_OpenFont("assets/fonts/ComicSansMS.ttf", 70);

  std::string chars = "";
  for(int i = ' '; i <= 'z'; i++)
  {
    chars += (char)i;
    chars += " ";
  }

  for(int i = 0; i < NUM_FONTS; i++)
  {
    SDL_Surface* surface = TTF_RenderText_Solid(fonts[i], chars.c_str(), 0, {255, 255, 255, 255});
    fontTextures[i] = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_DestroySurface(surface);
    surface = NULL;

    int totalWidth = 0;
    int currentWidth;
    int height = fontTextures[i]->h;
    int spaceSize;
    TTF_GetStringSize(fonts[i], chars.substr(0, 1).c_str(), 2 * sizeof(char), &spaceSize, NULL);

    for(int j = 0; j < chars.length(); j += 2)
    {
      int k = j/2 + 32;
      glyphs[i][k].x = totalWidth;
      glyphs[i][k].y = 0;
      glyphs[i][k].h = height;

      TTF_GetStringSize(fonts[i], chars.substr(j, 2).c_str(), 2 * sizeof(char), &currentWidth, NULL);

      glyphs[i][k].w = currentWidth - 10;
      totalWidth += currentWidth;
    }
  }
}

void Text::freeFonts()
{
  for(int i = 0; i < NUM_FONTS; i++)
  {
    TTF_CloseFont(fonts[i]);
    SDL_DestroyTexture(fontTextures[i]);
  }
}

Text::Text(SDL_Renderer* r, int f, std::string t)
{
  renderer = r;
  font = f;
  setText(t);
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
  if(text.length() <= 1)
  {
    return;
  }
  SDL_SetTextureColorMod(fontTextures[font], clr.x, clr.y, clr.z);

  int totalWidth = 0;
  int line = 0;
  int nextWord = 0;
  int pos = 0;

  SDL_FRect drawRect;

  nextWord = text.find(" ", nextWord);

  while(nextWord != std::string::npos) 
  {
    int currentWidth;
    TTF_GetStringSize(fonts[font], text.substr(pos, nextWord + 1 - pos).c_str(), 0, &currentWidth, NULL);
    
    if(totalWidth + currentWidth > rect.w)
    {
      line += fontTextures[font]->h;
      totalWidth = 0;
      pos++;
    }

    int wordWidth = 0;
    for(int i = pos; i < nextWord; i++)
    {
      SDL_FRect glyphRect = glyphs[font][text.at(i)];
      drawRect.x = rect.x + totalWidth + wordWidth;
      drawRect.y = rect.y + line;
      drawRect.w = glyphRect.w;
      drawRect.h = glyphRect.h; 

      SDL_RenderTexture(renderer, fontTextures[font], &glyphRect, &drawRect);

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
