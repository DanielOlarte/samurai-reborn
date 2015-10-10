
#include "GameFont.h"

Font::GameFont::GameFont(TTF_Font *newFont, SDL_Color color, std::string filename, int sizeFont, int idFont)
{
  id = idFont;
  font = NULL;
  font = newFont;
  this->color = color;
  this->filename = filename;
  this->sizeFont = sizeFont;
}

Font::GameFont::GameFont()
{
  font = NULL;
}

Font::GameFont::GameFont(const Font::GameFont& cSource)
{
  color = cSource.color;
  sizeFont = cSource.sizeFont;
  filename = cSource.filename;
  font = NULL;
  font = TTF_OpenFont(filename.c_str(), sizeFont);
}

Font::GameFont& Font::GameFont::operator=(const Font::GameFont& cSource)
{
  color = cSource.color;
  sizeFont = cSource.sizeFont;
  filename = cSource.filename;
  font = NULL;
  font = TTF_OpenFont(filename.c_str(), sizeFont);

  return *this;
}

Font::GameFont::~GameFont(void)
{
  TTF_CloseFont(font);
  font = NULL;
}
