
#include "SArenaWinner.h"
#include <PandaP1.h>

SArenaWinner::SArenaWinner(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_ARENA_WINNER);
  setProperty(MainStates::NORMAL_MENU);
}

SArenaWinner::~SArenaWinner(void)
{
}

void SArenaWinner::init()
{
  guiArenaWinnerMenu = new RPRGUI::GUIMenu();

  createGUI();

  gameCore->clearPlayerToInitialize();

  arenaWinnerMenu = new Image::MainMenuSelection(&controllers.at(0));
  arenaWinnerMenu->setNewIdGameState(MainStates::STATE_ARENA_WINNER);
  arenaWinnerMenu->setListButtons(&guiArenaWinnerMenu->getListButtons());

  numberOfPlayers = 1;
  
  GameSound::getInstance()->playSound(1,1,0);
  GameSound::getInstance()->downVolume(2, 0.95f);
  GameSound::getInstance()->upVolume(1, 100.0f);
}

void SArenaWinner::handleEvents()
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

void SArenaWinner::logic()
{
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  arenaWinnerMenu->setController(&controllers.at(i));
	  arenaWinnerMenu->setNumberOfPlayers(numberOfPlayers);
	  arenaWinnerMenu->setIsRunning(gameCore->getIsRunning());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *arenaWinnerMenu );

	  gameCore->setIsRunning(arenaWinnerMenu->getIsRunning());
	  gameCore->setCurrentGameMode(arenaWinnerMenu->getCurrentGameMode());

	  if ( arenaWinnerMenu->getNewIdGameState() != getNameState() )
	  {
		setHasEnded( arenaWinnerMenu->getNewIdGameState() );
		return;
	  }
	}
  }
}

void SArenaWinner::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiArenaWinnerMenu->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiArenaWinnerMenu->getTexturesStaticImages().at(i), 
		                        guiArenaWinnerMenu->getListStaticImages().at(i).getPosition(),
                                guiArenaWinnerMenu->getListStaticImages().at(i).getOffset().x, 
								guiArenaWinnerMenu->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiArenaWinnerMenu->getListButtons().size(); i++)
  {
    gameRender->drawButton(guiArenaWinnerMenu->getTextureButtons(),
		                   guiArenaWinnerMenu->getListButtons().at(i).getPosition(),
		                   guiArenaWinnerMenu->getListButtons().at(i).getDimensions(),
		                   guiArenaWinnerMenu->getListButtons().at(i).getTexturePosition());
  }

  SDL_GL_SwapBuffers();
}

void SArenaWinner::cleanUp()
{
  controllers.clear();

  delete guiArenaWinnerMenu;
  delete arenaWinnerMenu;
}

void SArenaWinner::createGUI()
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Arena Winner Menu/";

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

  guiArenaWinnerMenu->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiArenaWinnerMenu->addTextureStaticImages(gameRender->loadTexture(commonPath + "ArenaWinnerBackground.png"));  

  std::string filenameWinner = "Resources/Menus/Menu Selection Player/SuricataSelector.png";
  if ( gameCore->getMenuEndData().loserMode == SpriteData::MEERKAT )
  {
    filenameWinner = "Resources/Menus/Menu Selection Player/PandaSelector.png";
  }

  guiArenaWinnerMenu->addStaticImage( guiManager->createStaticImage(Vector2f(494.0f, 163.0f),
	                                                         Vector2f(288.0f, 384.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiArenaWinnerMenu->addTextureStaticImages(gameRender->loadTexture(filenameWinner));  
}

void SArenaWinner::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
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

void SArenaWinner::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  bool continueButton = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();
  bool back = inputs.actions.find(GameCoreStates::BACK) != inputs.actions.end();

  if ( continueButton )
  {
	menu.setCurrentGameMode(MainStates::ARENAS);
	menu.setNewIdGameState( MainStates::STATE_MENUSELECTIONPLAYER );
  }

  if ( back )
  {
    menu.setNewIdGameState( MainStates::STATE_MAINMENU );
  }
}