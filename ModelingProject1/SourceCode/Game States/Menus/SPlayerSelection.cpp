
#include "SPlayerSelection.h"

#include <PandaP1.h>
#include <Xinput.h>

SPlayerSelection::SPlayerSelection(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_MENUSELECTIONPLAYER);
  setProperty(MainStates::NORMAL_MENU);
}

SPlayerSelection::~SPlayerSelection(void)
{
  GameSound::getInstance()->closeSound();
}

void SPlayerSelection::init()
{
  guiSelectPlayer = new RPRGUI::GUIMenu();

  gameCore->getPlayersList().clear();
  gameCore->clearPlayerToInitialize();

  createGUI();

  menuSelectionPlayer = new Image::MenuSelectionPlayer(&controllers.at(0));
  menuSelectionPlayer->setNewIdGameState(MainStates::STATE_MENUSELECTIONPLAYER);
  numberOfPlayers = 1;
}

void SPlayerSelection::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {	
    controllers.at(i).getInputMapper()->clearCurrentMappedInput();
  }

  numberOfPlayers = gameInput->countActiveControllers(controllers);

  while ( SDL_PollEvent(&e) )
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
      case SDL_MOUSEMOTION:
      {
		customCursor.cursor->setPosition(mousePosition.x, mousePosition.y);
		arrowImage.optionSelected = guiSelectPlayer->checkMousePosition(mousePosition);
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

void SPlayerSelection::logic()
{
  checkSelectedPlayers();
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  menuSelectionPlayer->setController(&controllers.at(i));
	  menuSelectionPlayer->setCurrentSelection(controllers.at(i).getSelectedPlayer());
	  menuSelectionPlayer->setNumberOfPlayers(numberOfPlayers);
	  menuSelectionPlayer->setPlayerOneSelected(isPlayerOneSelected);
	  menuSelectionPlayer->setPlayerTwoSelected(isPlayerTwoSelected);
	  menuSelectionPlayer->setCurrentGameMode(gameCore->getCurrentGameMode());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *menuSelectionPlayer );
	  controllers.at(i).updatePositionController(i);

	  if ( menuSelectionPlayer->getNewIdGameState() != getNameState() )
	  {
		handleChangeOfState(menuSelectionPlayer->getNewIdGameState());
		setHasEnded( menuSelectionPlayer->getNewIdGameState() );
		return;
	  }
	}
  }
}

void SPlayerSelection::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiSelectPlayer->getListStaticImages().size(); i++)
  {
    gameRender->drawSpriteTexture(guiSelectPlayer->getTexturesStaticImages().at(i), 
		                          guiSelectPlayer->getListStaticImages().at(i).getPosition(),
								  guiSelectPlayer->getListStaticImages().at(i).getState(),
                                  guiSelectPlayer->getListStaticImages().at(i).getOffset().x, 
								  guiSelectPlayer->getListStaticImages().at(i).getOffset().y);
  }

  for ( std::string::size_type i = 0; i < controllers.size(); i++)
  {
    gameRender->drawSpriteTexture(controllers.at(i).getTexture(), controllers.at(i).getPosition(), controllers.at(i).getState(),
                                  controllers.at(i).getOffset().x, controllers.at(i).getOffset().y );
  }
      
  gameRender->drawFullTexture(customCursor.cursor->getTexture(), customCursor.cursor->getPosition(),
                              customCursor.cursor->getOffset().x, customCursor.cursor->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SPlayerSelection::cleanUp()
{
  controllers.clear();

  delete guiSelectPlayer;
  delete menuSelectionPlayer;

  delete customCursor.cursor;
}

void SPlayerSelection::createGUI( )
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Menu Selection Player/";

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 215.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "Keyboard.png", 
									Image::ENABLE, InputMapping::KEYBOARD) );
  controllers.at(0).setController(GameInput::initializeControllerData(getNameState(), InputMapping::KEYBOARD));
  controllers.at(0).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(0).getController(), InputMapping::KEYBOARD));
  controllers.at(0).getController()->setPlayerID(0);
  controllers.at(0).getController()->setWasPreviouslyPressedAllKeys();

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 310.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "Gamepad.png", 
									Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(1).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(1).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(1).getController(), InputMapping::GAMEPAD));
  controllers.at(1).getController()->setPlayerID(1);
  controllers.at(1).getController()->setWasPreviouslyPressedAllKeys();

  controllers.push_back( new Image::ImageController(Vector2f(590.0f, 405.0f), Vector2f(100.0f, 67.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "Gamepad.png", 
									Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(2).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(2).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(2).getController(), InputMapping::GAMEPAD));
  controllers.at(2).getController()->setPlayerID(2);
  controllers.at(2).getController()->setWasPreviouslyPressedAllKeys();

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  
  
  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "MenuCharacterSelectorBackground.png"));

  guiSelectPlayer->addStaticImage( new Image::ImageObject(Vector2f(200.0f, 130.0f), 
	                                                      Vector2f(288.0f, 384.0f), 
	                                                      Vector2f(0.0f, 0.0f) ) );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "PandaSelector.png"));

  guiSelectPlayer->addStaticImage( guiManager->createStaticImage(Vector2f(770.0f, 130.0f),
	                                                         Vector2f(288.0f, 384.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSelectPlayer->addTextureStaticImages(gameRender->loadTexture(commonPath + "SuricataSelector.png"));
}

void SPlayerSelection::checkSelectedPlayers()
{
  boost::ptr_vector<Image::ImageController>::iterator iter = controllers.begin();
  isPlayerOneSelected = false;
  isPlayerTwoSelected = false;

  for ( iter; iter != controllers.end(); iter++ )
  {
    if ( iter->getSelectedPlayer() == MenuData::PLAYER_ONE )
	{
	  isPlayerOneSelected = true;
	}
    if ( iter->getSelectedPlayer() == MenuData::PLAYER_TWO )
	{
	  isPlayerTwoSelected = true;
	}
  }
}

void SPlayerSelection::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
	  arrowImage.optionSelected = guiSelectPlayer->checkMousePosition(mousePosition);
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

void SPlayerSelection::handleChangeOfState(int idState)
{
  switch(idState)
  {
    case MainStates::STATE_LEVELONEJAPAN:
	case MainStates::STATE_ARENA_MODE:
	{
      for ( std::string::size_type i = 0; i < controllers.size(); i++)
      {
	    if ( controllers.at(i).getSelectedPlayer() != MenuData::NO_SELECTED_PLAYER )
		{
		  Image::PlayersInitialize initialize;
		  initialize.characterID = controllers.at(i).getSelectedPlayer();
		  if ( initialize.characterID == 2 )
		  {
		    initialize.characterID = 1;
		  }
		  initialize.controllerID = controllers.at(i).getController()->getPlayerID();

		  gameCore->pushBackPlayerToInitialize(initialize);
		}
      }
	  break;
	}
  }
}

void SPlayerSelection::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  const int RIGHT = 1;
  const int LEFT = -1;

  bool moveRight = inputs.actions.find(GameCoreStates::RIGHT) != inputs.actions.end();
  bool moveLeft = inputs.actions.find(GameCoreStates::LEFT) != inputs.actions.end();
  bool continueAction = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();
  bool backAction = inputs.actions.find(GameCoreStates::BACK) != inputs.actions.end();

  if ( moveRight )
  {
    if ( menu.getCurrentSelection() <= MenuData::NO_SELECTED_PLAYER && !menu.isPlayerTwoSelected() )
    {
	  GameSound::getInstance()->loadChunk(1, 1, 1);
	  menu.moveSelection(RIGHT);
	}
	if ( menu.getCurrentSelection() == MenuData::PLAYER_ONE && menu.isPlayerTwoSelected() )
	{
	  GameSound::getInstance()->loadChunk(1, 1, 1);
	  menu.moveSelection(RIGHT);
	}
  }

  if ( moveLeft )
  {
	if ( menu.getCurrentSelection() >= MenuData::NO_SELECTED_PLAYER && !menu.isPlayerOneSelected() )
	{
	  GameSound::getInstance()->loadChunk(1, 1, 1);
	  menu.moveSelection(LEFT);
	}
	if ( menu.getCurrentSelection() == MenuData::PLAYER_TWO && menu.isPlayerOneSelected() )
	{
	  GameSound::getInstance()->loadChunk(1, 1, 1);
	  menu.moveSelection(LEFT);
	}
  }

  if ( continueAction )
  {
	if ( menu.isPlayerOneSelected() || menu.isPlayerTwoSelected() )
	{
      if ( menu.getCurrentGameMode() == MainStates::LEVELS )
      {
        menu.setNewIdGameState(MainStates::STATE_LEVELONEJAPAN);
      }
	}
	if ( menu.isPlayerOneSelected() && menu.isPlayerTwoSelected() )
	{
      if ( menu.getCurrentGameMode() == MainStates::ARENAS )
      {
        menu.setNewIdGameState(MainStates::STATE_ARENA_MODE);
      }
	}
  }

  if ( backAction )
  {
    menu.setNewIdGameState(MainStates::STATE_MAINMENU);
  }
}