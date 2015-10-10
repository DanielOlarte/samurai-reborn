
#include <MenuSelectionPlayer.h>

Image::MenuSelectionPlayer::MenuSelectionPlayer(Image::ImageController* control)
{
  controller = control;
  currentSelection = controller->getSelectedPlayer();
}

Image::MenuSelectionPlayer::~MenuSelectionPlayer()
{
  listButtons.clear();
  listStaticImages.clear();
}

void Image::MenuSelectionPlayer::moveSelection(int direction)
{
  const int RIGHT = 1;
  const int LEFT = -1;

  switch(direction)
  {
    case RIGHT:
	{
	  if ( controller->getSelectedPlayer() != MenuData::PLAYER_TWO )
	  {
	    controller->setSelectedPlayer( controller->getSelectedPlayer() + direction );
	  }
	  break;
    }
    case LEFT:
	{
	  if ( controller->getSelectedPlayer() != MenuData::PLAYER_ONE )
	  {
	    controller->setSelectedPlayer( controller->getSelectedPlayer() + direction );
	  }
	  break;
    }
  }
  currentSelection = controller->getSelectedPlayer();
}