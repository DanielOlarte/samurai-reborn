#pragma once

#include <MenuSelection.h>

#include <ImageController.h>

namespace Image
{
  class MenuSelectionPlayer : public MenuSelection
  {
    public:
	  MenuSelectionPlayer() {};
	  MenuSelectionPlayer(Image::ImageController* control);
	  ~MenuSelectionPlayer();

	  Image::ImageObject& getController() { return *controller; }
	  void setController(Image::ImageController* control) { controller = control; }

	  void moveSelection(int direction);

    private:
	 Image::ImageController* controller;
  };
}