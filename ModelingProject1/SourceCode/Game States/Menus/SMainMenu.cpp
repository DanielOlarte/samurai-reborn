
#include "SMainMenu.h"
#include <PandaP1.h>

void Image::ArrowMainMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  }
  arrow->setPosition(420.0f, 280.0f + ( (optionSelected-1)*50.0f) );
}

SMainMenu::SMainMenu(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_MAINMENU);
  setProperty(MainStates::NORMAL_MENU);
}

SMainMenu::~SMainMenu(void)
{
}

void SMainMenu::init()
{
  guiMainMenu = new RPRGUI::GUIMenu();

  createGUI();

  gameCore->clearPlayerToInitialize();

  mainMenu = new Image::MainMenuSelection(&controllers.at(0));
  mainMenu->setNewIdGameState(MainStates::STATE_MAINMENU);
  mainMenu->setListButtons(&guiMainMenu->getListButtons());

  numberOfPlayers = 1;
  
  GameSound::getInstance()->playSound(1,1,0);
  GameSound::getInstance()->downVolume(2, 0.8f);
}

void SMainMenu::handleEvents()
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
		arrowImage.optionSelected = guiMainMenu->checkMousePosition(mousePosition);
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

void SMainMenu::logic()
{
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  mainMenu->setController(&controllers.at(i));
	  mainMenu->setCurrentSelection(arrowImage.optionSelected);
	  mainMenu->setNumberOfPlayers(numberOfPlayers);
	  mainMenu->setIsRunning(gameCore->getIsRunning());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *mainMenu );
	  arrowImage.optionSelected = mainMenu->getCurrentSelection();

	  gameCore->setIsRunning(mainMenu->getIsRunning());
	  gameCore->setCurrentGameMode(mainMenu->getCurrentGameMode());

	  if ( mainMenu->getNewIdGameState() != getNameState() )
	  {
		setHasEnded( mainMenu->getNewIdGameState() );
		return;
	  }
	}
  }
  arrowImage.updatePositionArrow();
}

void SMainMenu::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiMainMenu->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiMainMenu->getTexturesStaticImages().at(i), 
		                        guiMainMenu->getListStaticImages().at(i).getPosition(),
                                guiMainMenu->getListStaticImages().at(i).getOffset().x, 
								guiMainMenu->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiMainMenu->getListButtons().size(); i++)
  {
    gameRender->drawButton(guiMainMenu->getTextureButtons(),
		                   guiMainMenu->getListButtons().at(i).getPosition(),
		                   guiMainMenu->getListButtons().at(i).getDimensions(),
		                   guiMainMenu->getListButtons().at(i).getTexturePosition());
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

void SMainMenu::cleanUp()
{
  controllers.clear();

  delete arrowImage.arrow;
  delete customCursor.cursor;

  delete guiMainMenu;
  delete mainMenu;
}

void SMainMenu::createGUI()
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Main Menu/";

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

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(412.0f, 64.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "MainMenuHighlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  

  guiMainMenu->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiMainMenu->addTextureStaticImages(gameRender->loadTexture(commonPath + "MainMenuBackground.png"));

  guiMainMenu->addButton( guiManager->createButton(MenuData::HISTORY_MODE, Vector2f(522.0f, 300.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 0.0f),
	                                               MainStates::STATE_MENUSELECTIONPLAYER,
												   MainStates::LEVELS) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::TUTORIAL, Vector2f(522.0f, 350.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 28.75f),
	                                               MainStates::STATE_MENUSELECTIONPLAYER,
												   MainStates::ARENAS) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::CREDITS, Vector2f(522.0f, 400.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 57.5f),
												   MainStates::STATE_CREDITS,
												   MainStates::MENUS) );
  guiMainMenu->addButton( guiManager->createButton(MenuData::QUIT, Vector2f(522.0f, 450.0f), 
	                                               Vector2f(230.0f, 28.75f), Vector2f(0.0f, 86.25f),
	                                               MainStates::STATE_EXIT,
												   MainStates::MENUS) );
  guiMainMenu->addTextureButtons( gameRender->loadTexture(commonPath + "MainMenuButtons.png") );                                               
}

void SMainMenu::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      arrowImage.optionSelected = guiMainMenu->checkMousePosition(mousePosition);
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

void SMainMenu::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  const int UP = -1;
  const int DOWN = 1;

  bool moveUp = inputs.actions.find(GameCoreStates::UP) != inputs.actions.end();
  bool moveDown = inputs.actions.find(GameCoreStates::DOWN) != inputs.actions.end();
  bool pressedButton = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();
  bool back = inputs.actions.find(GameCoreStates::BACK) != inputs.actions.end();

  if ( moveUp )
  {
	GameSound::getInstance()->loadChunk(1, 1, 1);
    if ( menu.getCurrentSelection() - 1 == MenuData::NOTHING_SELECTED ||
		 menu.getCurrentSelection() == MenuData::NOTHING_SELECTED)
    {
	  menu.setCurrentSelection(MenuData::QUIT);
	}
	else
	{
	  menu.moveSelection(UP);
	}
  }

  if ( moveDown )
  {
	GameSound::getInstance()->loadChunk(1, 1, 1);
    if ( menu.getCurrentSelection() + 1 > MenuData::QUIT )
    {
	  menu.setCurrentSelection(MenuData::HISTORY_MODE);
    }
	else
	{
	  menu.moveSelection(DOWN);
	}
  }

  if ( pressedButton )
  {
	bool running = menu.getIsRunning();
	int gameMode = menu.getCurrentGameMode();
	if ( menu.getCurrentSelection() != MenuData::NOTHING_SELECTED )
    {
	  menu.setNewIdGameState( menu.getListButtons().at( menu.getCurrentSelection() - 1 ).eventClicked(&running, &gameMode) );
	}
	menu.setIsRunning(running);
	menu.setCurrentGameMode(gameMode);
  }

  if ( back )
  {
    menu.setCurrentSelection(MenuData::QUIT);
  }
}