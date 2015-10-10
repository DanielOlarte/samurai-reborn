#pragma once

#include "GameInputMapper.h"

#include <ImageController.h>

class GameInput
{
  public:
   GameInput(void);
   ~GameInput(void);

   bool handleWindowEvents();
   void handleKeyEvents(InputMapping::GameInputMapper* gameInputMapper, InputMapping::Controller* controller);

   static InputMapping::GameInputMapper* initializeGameInputMapperData(int currentState, InputMapping::Controller& controller, 
	                                                                   int typeController);
   static InputMapping::Controller* initializeControllerData(int currentState, int typeController);
   int countActiveControllers(boost::ptr_vector<Image::ImageController>& controllers);
};

