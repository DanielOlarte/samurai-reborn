#pragma once

#include <Bar.h>

#include <Vector.h>

#include <string>

namespace RPRGUI
{
  class SoundBar : public Bar
  {
    public:
     SoundBar(int id, std::string filename);
	 ~SoundBar();

	 void draw();

	 void updateCurrentBarFrame();

	 int getCurrentBarFrame() { return currentBarFrame; }

    private:
	 GLuint textureBar;
	 int currentBarFrame, maxBarFrames;
	 
	 Vector2f position, imageDimensions;
  };
}