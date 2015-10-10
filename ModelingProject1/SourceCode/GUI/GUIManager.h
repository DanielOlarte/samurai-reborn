#pragma once

#include "Vector.h"

#include "MenuData.h"

#include "PushButton.h"
#include "ImageObject.h"

namespace RPRGUI
{
  class GUIManager
  {
    public:
     GUIManager(void);
     ~GUIManager(void);

     PushButton* createButton(int id, Vector2f pos, Vector2f dimensions, Vector2f posTexture, int idChangeState,
		                      int gameMode = 0);
     Image::ImageObject* createStaticImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, std::string filename);
  };
}

