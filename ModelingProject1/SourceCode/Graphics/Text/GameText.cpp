
#include "GameText.h"

Text::GameText::GameText(std::string text, Vector2f pos, Vector2f off)
	: TextObject(text, pos, off)
{
}

Text::GameText::~GameText(void)
{
  dataText.clear();
  delete font;
}

void Text::GameText::initializeFont(Font::GameFont* newFont)
{
  font = newFont;
}

void Text::GameText::setDataText(int data)
{
}