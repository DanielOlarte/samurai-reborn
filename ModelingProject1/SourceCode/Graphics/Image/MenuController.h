#pragma once

#include <ImageObject.h>

#include <GameInputMapper.h>
#include <Controller.h>

namespace Image
{
  class MenuController : public ImageObject
  {
    public:
	 MenuController(int state, int type);
	 MenuController() {};
	 ~MenuController();

     InputMapping::GameInputMapper* getInputMapper() { return inputMapper; }
	 void setGameInputMapper(InputMapping::GameInputMapper* mapper) { inputMapper = mapper; }

	 InputMapping::Controller* getController() { return controller; }
	 void setController(InputMapping::Controller* control) { controller = control; }

	 int getState() { return state; }
	 void setState(int newState) { state = newState; }

    private:
     InputMapping::GameInputMapper* inputMapper;
	 InputMapping::Controller* controller;
	 int state, typeController;
  };
}