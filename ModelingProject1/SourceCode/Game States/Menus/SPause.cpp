
#include "SPause.h"
#include <PandaP1.h>

void Image::ArrowPauseMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  } 

  arrow->setPosition(430.0f, 280.0f + ( (optionSelected-1)*50.0f) );
}

SPause::SPause(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_PAUSE);
  setProperty(MainStates::MENU_IN_GAME);
}

SPause::~SPause(void)
{
}

void SPause::init()
{
  guiPauseMenu = new RPRGUI::GUIMenu();

  createGUI();

  GameSound::getInstance()->playAdditionalSound(3,1,0);

  gameCore->clearPlayerToInitialize();
  pauseMenu = new Image::MainMenuSelection(&controllers.at(0));
  pauseMenu->setNewIdGameState(MainStates::STATE_PAUSE);
  pauseMenu->setListButtons(&guiPauseMenu->getListButtons());
  numberOfPlayers = 1;
}

void SPause::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {	
    controllers.at(i).getInputMapper()->clearCurrentMappedInput();
  }

  while ( SDL_PollEvent(&e) && checkIfStateEnd() == getNameState() )
  {
	Vector2f mousePosition = Vector2f(static_cast<float>(e.motion.x), static_cast<float>(e.motion.y) );

    for (std::string::size_type i = 0; i < controllers.size(); i++)
    {	
	  if ( controllers.at(i).getController()->isEnabled() )
	  {
        gameInput->handleKeyEvents( controllers.at(i).getInputMapper(), 
		                            controllers.at(i).getController() );
	  }
    }

    switch( e.type )
    {
      case SDL_MOUSEBUTTONUP:
      {
        handleMouseUp(e.button.button, mousePosition);
		controllers.at(0).getInputMapper()->pushBackActionOnMappedInput(GameCoreStates::CONTINUE);
        break;
      }
      case SDL_MOUSEMOTION:
      {
        customCursor.cursor->setPosition(mousePosition.x, mousePosition.y);
		arrowImage.optionSelected = guiPauseMenu->checkMousePosition(mousePosition);
        break;
      }
      case SDL_QUIT:
      {
        gameCore->setIsRunning(false);
        return;
      }
    }
  }

  for (std::string::size_type i = 1; i < controllers.size(); i++)
  {	
	if ( controllers.at(i).getController()->isEnabled() )
	{
      gameInput->handleKeyEvents( controllers.at(i).getInputMapper(), 
		                          controllers.at(i).getController() );
	}
  }
}

void SPause::logic()
{
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  pauseMenu->setController(&controllers.at(i));
	  pauseMenu->setCurrentSelection(arrowImage.optionSelected);
	  pauseMenu->setNumberOfPlayers(numberOfPlayers);
	  pauseMenu->setIsRunning(gameCore->getIsRunning());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *pauseMenu );
	  arrowImage.optionSelected = pauseMenu->getCurrentSelection();

	  gameCore->setIsRunning(pauseMenu->getIsRunning());

	  if ( pauseMenu->getNewIdGameState() != getNameState() )
	  {
		setHasEnded( pauseMenu->getNewIdGameState() );
		return;
	  }
	}
  }
  arrowImage.updatePositionArrow();
}

void SPause::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiPauseMenu->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiPauseMenu->getTexturesStaticImages().at(i), 
		                        guiPauseMenu->getListStaticImages().at(i).getPosition(),
                                guiPauseMenu->getListStaticImages().at(i).getOffset().x, 
								guiPauseMenu->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiPauseMenu->getListButtons().size(); i++)
  {
    gameRender->drawButton(guiPauseMenu->getTextureButtons(),
		                   guiPauseMenu->getListButtons().at(i).getPosition(),
		                   guiPauseMenu->getListButtons().at(i).getDimensions(),
		                   guiPauseMenu->getListButtons().at(i).getTexturePosition());
  }

  if ( arrowImage.optionSelected != MenuData::NOTHING_SELECTED )
  {
    gameRender->drawFullTexture(arrowImage.arrow->getTexture(), arrowImage.arrow->getPosition(),
                                arrowImage.arrow->getOffset().x, arrowImage.arrow->getOffset().y);
  }

  gameRender->drawFullTexture(customCursor.cursor->getTexture(), customCursor.cursor->getPosition(),
                              customCursor.cursor->getOffset().x, customCursor.cursor->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SPause::cleanUp()
{
  controllers.clear();

  delete arrowImage.arrow;
  delete customCursor.cursor;

  delete guiPauseMenu;
  delete pauseMenu;
  delete timer;
}

void SPause::createGUI()
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Pause Menu/";

  controllers.push_back( new Image::MenuController(Image::ENABLE, InputMapping::KEYBOARD) );
  controllers.at(0).setController(GameInput::initializeControllerData(getNameState(), InputMapping::KEYBOARD));
  controllers.at(0).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(0).getController(), InputMapping::KEYBOARD));
  controllers.at(0).getController()->setPlayerID(0);
  controllers.at(0).getController()->setWasPreviouslyPressedAllKeys();

  controllers.push_back( new Image::MenuController(Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(1).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(1).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(1).getController(), InputMapping::GAMEPAD));
  controllers.at(1).getController()->setPlayerID(1);
  controllers.at(1).getController()->setWasPreviouslyPressedAllKeys();

  controllers.push_back( new Image::MenuController(Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(2).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(2).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(2).getController(), InputMapping::GAMEPAD));
  controllers.at(2).getController()->setPlayerID(2);
  controllers.at(2).getController()->setWasPreviouslyPressedAllKeys();

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(430.0f, 64.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "PauseMenuHighlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  

  guiPauseMenu->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiPauseMenu->addTextureStaticImages(gameRender->loadTexture(commonPath + "PauseMenuBackground.png")); 

  guiPauseMenu->addButton( guiManager->createButton(MenuData::CONTINUE_GAME, Vector2f(510.0f, 300.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 0.0f),
	                                               MainStates::STATE_IN_GAME) );
  guiPauseMenu->addButton( guiManager->createButton(MenuData::SOUND, Vector2f(510.0f, 350.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 32.0f),
	                                               MainStates::STATE_SOUNDS_OPTIONS) );
  guiPauseMenu->addButton( guiManager->createButton(MenuData::MAIN_MENU, Vector2f(510.0f, 400.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 64.0f),
	                                               MainStates::STATE_MAINMENU) );

  guiPauseMenu->addTextureButtons( gameRender->loadTexture(commonPath + "PauseMenuButtons.png") );     
}

void SPause::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      arrowImage.optionSelected = guiPauseMenu->checkMousePosition(mousePosition);
      break;
    }
    case SDL_BUTTON_MIDDLE:
    {
      break;
    }
    case SDL_BUTTON_RIGHT:
    {
      break;
    }
  }
}

void SPause::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  const int UP = -1;
  const int DOWN = 1;

  bool moveUp = inputs.actions.find(GameCoreStates::UP) != inputs.actions.end();
  bool moveDown = inputs.actions.find(GameCoreStates::DOWN) != inputs.actions.end();
  bool pressedButton = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();
  bool unpause = inputs.actions.find(GameCoreStates::UNPAUSE) != inputs.actions.end();

  if ( moveUp )
  {
	GameSound::getInstance()->playAdditionalChunk(3, 1, 1);
    if ( menu.getCurrentSelection() - 1 == MenuData::NOTHING_SELECTED ||
		 menu.getCurrentSelection() == MenuData::NOTHING_SELECTED)
    {
	  menu.setCurrentSelection(MenuData::MAIN_MENU);
	}
	else
	{
	  menu.moveSelection(UP);
	}
  }

  if ( moveDown )
  {
	GameSound::getInstance()->playAdditionalChunk(3, 1, 1);
    if ( menu.getCurrentSelection() + 1 > MenuData::MAIN_MENU )
    {
	  menu.setCurrentSelection(MenuData::CONTINUE_GAME);
    }
	else
	{
      menu.moveSelection(DOWN);
	}
  }

  if ( pressedButton )
  {
	bool running = menu.getIsRunning();
	int gameMode = 0;
	if ( menu.getCurrentSelection() != MenuData::NOTHING_SELECTED )
    {
      int newState = (menu.getListButtons().at( menu.getCurrentSelection() - 1 ).eventClicked(&running, &gameMode));
	  menu.setNewIdGameState(newState);

	  if( newState == MainStates::STATE_MAINMENU )
	  {
	    GameSound::getInstance()->unpauseSystem();
	    GameSound::getInstance()->closeAll();
      }
	  if( newState == MainStates::STATE_IN_GAME )
	  {
	    GameSound::getInstance()->unpauseSystem();
      }
    }
	menu.setIsRunning(running);
  }

  if ( unpause )
  {
	GameSound::getInstance()->unpauseSystem();
    menu.setNewIdGameState(MainStates::STATE_LEVELONEJAPAN);
  }
}