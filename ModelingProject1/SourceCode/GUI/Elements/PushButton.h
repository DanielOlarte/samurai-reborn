#pragma once

#include "Vector.h"

#include "MenuData.h"

namespace RPRGUI
{
  class PushButton
  {
    public:
	 PushButton(int id, Vector2f pos, Vector2f dim, Vector2f textPos);
	 ~PushButton(void);

	 Vector2f getPosition() { return position; }

	 Vector2f getDimensions() { return dimensions; }

	 Vector2f getTexturePosition() { return texturePosition; }

	 int getID() { return id; }

	 void setIdChangeState(int id) { idChangeState = id; }

	 void setIdGameMode(int mode) { idGameMode = mode; }

	 int eventClicked(bool* isRunning, int* gameMode);

    private:
     int id;
	 Vector2f position;
	 Vector2f dimensions;
	 Vector2f texturePosition;
	 int idChangeState;
	 int idGameMode;
  };
}

