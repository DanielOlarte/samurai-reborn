
#include "SDL/SDL.h"

#include <windows.h>

#include "GameInput.h"

#include <Keyboard.h>
#include <Gamepad.h>

#include <SMainMenu.h>
#include <SPlayerSelection.h>
#include <SPause.h>
#include <SSoundOptions.h>
#include <SArenaWinner.h>
#include <SCredits.h>
#include <Player.h>

GameInput::GameInput(void)
{
}

GameInput::~GameInput(void)
{
}

bool GameInput::handleWindowEvents()
{
  SDL_Event evento;

  while( SDL_PollEvent( &evento ) )
  {     
    if( evento.type == SDL_QUIT)
    {
      return false;
    }
  }

  return true;
}

void GameInput::handleKeyEvents(InputMapping::GameInputMapper* gameInputMapper, InputMapping::Controller* controller)
{
  gameInputMapper->processNewInput(*controller);
}

InputMapping::GameInputMapper* GameInput::initializeGameInputMapperData(int currentState, InputMapping::Controller& controller, 
	                                                                    int typeController)
{
  InputMapping::GameInputMapper* inputMapper = new InputMapping::GameInputMapper(controller.getFileContextList()); 
  std::string nameContext = "";

  switch( currentState )
  {
    case MainStates::STATE_MAINMENU:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardmainmenucontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadmainmenucontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SMainMenu::inputCallback, 0);
	  break;
    }
    case MainStates::STATE_MENUSELECTIONPLAYER:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardmenucontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadmenucontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SPlayerSelection::inputCallback, 0);
	  break;
    }
    case MainStates::STATE_PAUSE:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardpausemenucontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadpausemenucontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SPause::inputCallback, 0);
	  break;
    }
    case MainStates::STATE_SOUNDS_OPTIONS:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardsoundmenucontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadsoundmenucontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SSoundOptions::inputCallback, 0);
	  break;
    }
	case MainStates::STATE_ARENA_WINNER:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardarenawinnercontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadarenawinnercontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SArenaWinner::inputCallback, 0);
	  break;
    }
	case MainStates::STATE_CREDITS:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardcreditsmenucontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadcreditsmenucontext";
		  break;
	    }
      }
	  inputMapper->addCallback(SCredits::inputCallback, 0);
	  break;
    }
    default:
    {
	  switch( controller.getTypeController() )
	  {
	    case InputMapping::KEYBOARD:
		{
		  nameContext = "keyboardcontext";
		  break;
        }
	    default:
        {
		  nameContext = "gamepadcontext";
		  break;
	    }
      }

	  inputMapper->addCallback(Characters::Player::inputCallback, 0);
	  break;
    }
  }

  inputMapper->pushContext(nameContext);

  controller.initializeKeys(inputMapper->getListKeys(), inputMapper->getStateMap(), inputMapper->getActionMap());
  return inputMapper;
}

InputMapping::Controller* GameInput::initializeControllerData(int currentState, int typeController)
{
  std::string fileContextList = "";
  std::string nameContext = "";

  switch( typeController )
  {
    case InputMapping::KEYBOARD:
    {
	  fileContextList = "Resources/Input/KeyboardContextList.txt";
      return new InputMapping::Keyboard(0, fileContextList);
	  break;
    }
	default:
    {
	  fileContextList = "Resources/Input/GamepadContextList.txt";
	  return new InputMapping::Gamepad(0, fileContextList);
	  break;
    }
  }

  return new InputMapping::Keyboard(0, fileContextList);
}

int GameInput::countActiveControllers(boost::ptr_vector<Image::ImageController>& controllers)
{
  boost::ptr_vector<Image::ImageController>::iterator iter = controllers.begin();
  iter++;

  int count = 1;

  for ( iter; iter != controllers.end(); iter++ )
  {
	bool stateController = iter->getController()->isEnabled();
	if ( stateController )
	{
	  count += 1;
	}
	iter->setState(stateController);
  }

  return count;
}