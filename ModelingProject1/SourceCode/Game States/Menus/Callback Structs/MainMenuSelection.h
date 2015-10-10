#pragma once

#include <MenuSelection.h>
#include <MenuController.h>

namespace Image
{
  class MainMenuSelection : public MenuSelection
  {
    public:
	  MainMenuSelection() {};
	  MainMenuSelection(Image::MenuController* control);
	  ~MainMenuSelection();

	  Image::ImageObject& getController() { return *controller; }
	  void setController(Image::MenuController* control) { controller = control; }

	  void moveSelection(int direction);

    private:
	  Image::MenuController* controller;
  };
}