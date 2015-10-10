
#include <MenuController.h>

Image::MenuController::MenuController(int state, int type)
{
  this->state = state;
  typeController = type;
}

Image::MenuController::~MenuController()
{
  delete inputMapper;
  delete controller;
}