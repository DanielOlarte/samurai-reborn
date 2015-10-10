
#include <MenuSelection.h>

Image::ImageObject& Image::MenuSelection::getController()
{
  Image::ImageObject* temporalImage = new Image::ImageObject(); 
  return *temporalImage;
}

Image::MenuSelection::~MenuSelection()
{
  listButtons.clear();
  listStaticImages.clear();
}