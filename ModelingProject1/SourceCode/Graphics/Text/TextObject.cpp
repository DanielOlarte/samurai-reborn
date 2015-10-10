
#include <TextObject.h>

Text::TextObject::TextObject(std::string text, Vector2f pos, Vector2f off)
{
  dataText = text;
  position = pos;
  offset = off;
}

Text::TextObject::~TextObject()
{
}