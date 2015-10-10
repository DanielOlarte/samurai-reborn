#pragma once

class GameConfiguration
{
  public:
   GameConfiguration(void);
   ~GameConfiguration(void);
   void getConfiguration(void);

  private:
   int difficultyLevel;
   int soundMode;
};

