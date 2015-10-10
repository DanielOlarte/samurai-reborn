#pragma once

#include <boost/ptr_container/ptr_vector.hpp>

#include <vector>

#include "PushButton.h"
#include "ImageObject.h"
#include <Bar.h>

namespace RPRGUI
{
  class GUIMenu
  {
    public:
	 GUIMenu(void);
	 ~GUIMenu(void);

	 void addButton(RPRGUI::PushButton* button) { listButtons.push_back(button); }
	 void addBar(RPRGUI::Bar* bar) { listBars.push_back(bar); }
	 void addStaticImage(Image::ImageObject* image) { listStaticImages.push_back(image); }
	 void addTextureButtons(GLuint texture) { textureButtons = texture; }

	 int checkMousePosition(Vector2f mousePosition);

	 GLuint getTextureButtons() { return textureButtons; }

	 boost::ptr_vector<Image::ImageObject>& getListStaticImages() { return listStaticImages; }
	 boost::ptr_vector<RPRGUI::PushButton> getListButtons() { return listButtons; }
	 boost::ptr_vector<RPRGUI::Bar>& getListBars() { return listBars; }

	 void addTextureStaticImages(GLuint texture) { texturesStaticImages.push_back(texture); }
	 std::vector<GLuint> getTexturesStaticImages() { return texturesStaticImages; }

    private:
     boost::ptr_vector<RPRGUI::PushButton> listButtons;
	 boost::ptr_vector<RPRGUI::Bar> listBars;
     boost::ptr_vector<Image::ImageObject> listStaticImages;
	 std::vector<GLuint> texturesStaticImages;
	 GLuint textureButtons;
  };
}

