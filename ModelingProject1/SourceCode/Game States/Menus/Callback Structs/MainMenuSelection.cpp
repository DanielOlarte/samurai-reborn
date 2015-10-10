#include <MainMenuSelection.h>

Image::MainMenuSelection::MainMenuSelection(Image::MenuController* control)
{
  controller = control;
}

Image::MainMenuSelection::~MainMenuSelection()
{
  listButtons.clear();
  listStaticImages.clear();
}

void Image::MainMenuSelection::moveSelection(int direction)
{
  currentSelection += direction;
}