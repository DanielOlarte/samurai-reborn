
#include "GUIManager.h"
#include "GameRender.h"

RPRGUI::GUIManager::GUIManager(void)
{
}

RPRGUI::GUIManager::~GUIManager(void)
{
}

RPRGUI::PushButton* RPRGUI::GUIManager::createButton(int id, Vector2f pos, Vector2f dimensions, 
                                                     Vector2f posTexture, int idChangeState,
													 int gameMode)
{
  PushButton* newButton = new RPRGUI::PushButton(id, pos, dimensions, posTexture);
  newButton->setIdChangeState(idChangeState);
  newButton->setIdGameMode(gameMode);
  return newButton;
}

Image::ImageObject* RPRGUI::GUIManager::createStaticImage(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
                                                       std::string filename)
{
  return new Image::ImageObject(imagePosition, imageOffset, texturePosition);
}