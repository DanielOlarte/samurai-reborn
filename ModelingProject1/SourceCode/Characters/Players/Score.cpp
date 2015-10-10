#include "Score.h"
#include "GameRender.h"

#include <StringParser.h>

PlayerScore::Score::Score(void)
{
  points = 0;
}

PlayerScore::Score::~Score(void)
{
}

void PlayerScore::Score::drawDisplayPoints()
{
  std::string score = pointsDisplay.getDataText();
  std::string::iterator pointsIterator = score.begin();
  int currentNumber = 0;

  Vector2f dimensionsTexture = Vector2f(140.0f, 14.0f);
  Vector2f dimensionsNumber = Vector2f(14.0f, 14.0f);

  for (pointsIterator; pointsIterator < score.end(); pointsIterator++)
  {
    Vector2f positionNumber = pointsDisplay.getPosition();
    positionNumber.x = positionNumber.x + currentNumber*(14.0f);
	GameRender::drawSpriteTexture(pointsDisplay.getTextureNumbers(), positionNumber, parseStringToInt(*pointsIterator),
								  dimensionsNumber.x, dimensionsNumber.y);
    currentNumber++;
  }
}

void PlayerScore::Score::initializeTextAndFonts(std::string text, int idNumberPlayer, std::string filename)
{
  pointsDisplay = Text::ScoreText( text, Vector2f(170.0f*(idNumberPlayer) + 108.0f, 107.0f),
	                                     Vector2f(50.0f, 20.0f) );
  pointsDisplay.initializeNumbersTexture(filename);
  pointsDisplay.setDataText( points );
}

void PlayerScore::Score::addPoints(int value)
{
  points += value;
  pointsDisplay.setDataText( points );
}

