#pragma once

#include "ScoreText.h"

namespace PlayerScore
{
  class Score
  {
   public:
    Score(void);
    ~Score(void);

    void drawDisplayPoints();

    void initializeTextAndFonts(std::string text, int idNumberPlayer, std::string filename);

    int getPoints() { return points; }
    void addPoints(int value);

   private:
    Text::ScoreText pointsDisplay;
    int points;
  };
}
