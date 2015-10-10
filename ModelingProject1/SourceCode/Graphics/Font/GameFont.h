#pragma once

#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

namespace Font
{
  class GameFont
  {
    public:
     GameFont(TTF_Font* newFont, SDL_Color color, std::string filename, int sizeFont, int idFont);
     GameFont();

     GameFont(const GameFont& cSource);
     GameFont& operator=(const GameFont& cSource);
    ~GameFont(void);

     TTF_Font* getFont() { return font; }
     void setFont(TTF_Font* f) { font = f; }

     SDL_Color getColor() { return color; }
     void setColor(SDL_Color c) { color = c; }

     int getSizeFont() { return sizeFont; }

    private:
     TTF_Font* font;
     SDL_Color color;
     std::string filename;
     int id;
     int sizeFont;
  };
}