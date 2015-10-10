
#include "GUIMenu.h"

RPRGUI::GUIMenu::GUIMenu(void)
{
}

RPRGUI::GUIMenu::~GUIMenu(void)
{
  listButtons.clear();
  listStaticImages.clear();
  listBars.clear();
  
  for (std::string::size_type i = 0; i < texturesStaticImages.size(); i++)
  {
    glDeleteTextures(1, &texturesStaticImages.at(i));
  }

  texturesStaticImages.clear();
  glDeleteTextures(1, &textureButtons);
}

int RPRGUI::GUIMenu::checkMousePosition(Vector2f mousePosition)
{
  for (std::string::size_type i = 0; i < listButtons.size(); i++)
  {
    RPRGUI::PushButton& button = listButtons.at(i);
    Vector2f offset = Vector2f(button.getPosition().x + button.getDimensions().x, 
                               button.getPosition().y + button.getDimensions().y);

    if ( mousePosition.x >= button.getPosition().x && mousePosition.x <= offset.x &&
         mousePosition.y >= button.getPosition().y && mousePosition.y <= offset.y )
    {
      return button.getID();
    }
  }

  return MenuData::NOTHING_SELECTED;
}
