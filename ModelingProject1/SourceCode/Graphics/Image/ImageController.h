#pragma once

#include <ImageObject.h>

#include <GameInputMapper.h>
#include <Controller.h>

namespace Image
{
  class ImageController : public ImageObject
  {
    public:
     ImageController(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, 
		             std::string filename, int state, int type);
	 ImageController() {};
	 ~ImageController();

     void updatePositionController(int idController);
	 
     InputMapping::GameInputMapper* getInputMapper() { return inputMapper; }
	 void setGameInputMapper(InputMapping::GameInputMapper* mapper) { inputMapper = mapper; }

	 InputMapping::Controller* getController() { return controller; }
	 void setController(InputMapping::Controller* control) { controller = control; }

	 GLuint getTexture() { return texture; }

	 int getState() { return state; }
	 void setState(int newState) { state = newState; }

	 int getSelectedPlayer() { return selectedPlayer; }
	 void setSelectedPlayer(int player) { selectedPlayer = player; }

    private:
     GLuint texture;
     InputMapping::GameInputMapper* inputMapper;
	 InputMapping::Controller* controller;
	 int selectedPlayer, state, typeController;
  };
}