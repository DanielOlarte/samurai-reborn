
#include <ScoreText.h>

#include <GameRender.h>

#include <StringParser.h>

Text::ScoreText::ScoreText(std::string text, Vector2f pos, Vector2f off)
	: TextObject(text, pos, off)
{
}

Text::ScoreText::~ScoreText()
{
  dataText.clear();
  glDeleteTextures(1, &textureNumbers);
}

void Text::ScoreText::initializeNumbersTexture(std::string filename)
{
  textureNumbers = GameRender::loadTexture(filename);
}

void Text::ScoreText::setDataText(int data)
{
  dataText = parseDataToString(data);
  if ( data < 100 )
  {
	for ( ; dataText.size() < 3; )
	{
	  dataText = "0" + dataText;
	}
  }
}