#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <TextObject.h>

#include "GameFont.h"

namespace Text
{
  class GameText : public TextObject
  {
    public:
     GameText(std::string text, Vector2f pos, Vector2f off);
     ~GameText(void);

	 void initializeFont(Font::GameFont* newFont);

     Font::GameFont* getFont() { return font; }

	 void setDataText(int data);

    private:
     Font::GameFont* font;
  };
}

