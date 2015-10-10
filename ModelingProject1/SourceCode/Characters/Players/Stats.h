#pragma once

#include <windows.h>
#include <gl\GL.h>

#include <vector>

#include "GameImage.h"
#include <ImageHealth.h>

namespace PlayerStats
{
  struct Health
  {
    Image::ImageObject* healthBar;
	std::vector< Image::ImageHealth > healthForms;

    int pointsOfLife, maxPointsOfLife;
  };

  struct FaceState
  {
	Image::GameImage* faces;
	int currentFaceState;
	int maxFaces;
  };

  class Stats
  {
   public:
    Stats(void);
    ~Stats(void);

	void initializeFaceStates(std::string filename, int idPlayer);

	void drawFaceState();
	void drawSkullKills();
    void drawHealthBar();
    void drawHealth();

	void updateFaceState();
	void updateHealthBar();

	void takeDamage(int damage);

	int getHealth() { return health.pointsOfLife; }

   private:
    Health health;
	FaceState faces;
	Image::ImageObject* skullKills;
	GLuint textureHealthKills;
  };
}