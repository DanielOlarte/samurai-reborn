
#include <ImageController.h>

#include <GameRender.h>

Image::ImageController::ImageController(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
	                                    std::string filename, int state, int type)
{
  position = imagePosition;
  offset = imageOffset;
  this->texturePosition = texturePosition;
  texture = GameRender::loadTexture(filename);
  selectedPlayer = MenuData::NO_SELECTED_PLAYER;
  this->state = state;
  typeController = type;
}

Image::ImageController::~ImageController()
{
  glDeleteTextures(1, &texture);
}

void Image::ImageController::updatePositionController(int idController)
{
  if ( selectedPlayer == MenuData::NO_SELECTED_PLAYER )
  {
    setPosition(590.0f, 215.0f + (idController)*95.0f);
    return;
  }

  setPosition(520.0f + (selectedPlayer)*66.0f, 215.0f + (idController)*95.0f);
}