#include "SSoundOptions.h"

#include <SoundBar.h>
#include <PandaP1.h>

#include <GameSound.h>

void Image::ArrowSoundMenu::updatePositionArrow()
{
  if ( optionSelected == MenuData::NOTHING_SELECTED )
  {
    return;
  } 
  arrow->setPosition(372.0f, 260.0f + ( (optionSelected-1)*100.0f) );
}

SSoundOptions::SSoundOptions(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_SOUNDS_OPTIONS);
  setProperty(MainStates::MENU_IN_GAME);
}

SSoundOptions::~SSoundOptions(void)
{
}

void SSoundOptions::init()
{
  guiSoundMenu = new RPRGUI::GUIMenu();

  createGUI();

  gameCore->clearPlayerToInitialize();

  soundMenu = new Image::MainMenuSelection(&controllers.at(0));
  soundMenu->setNewIdGameState(MainStates::STATE_SOUNDS_OPTIONS);
  soundMenu->setListButtons(&guiSoundMenu->getListButtons());

  numberOfPlayers = 1;
}

void SSoundOptions::handleEvents()
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
		arrowImage.optionSelected = guiSoundMenu->checkMousePosition(mousePosition);
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

void SSoundOptions::logic()
{
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  soundMenu->setController(&controllers.at(i));
	  soundMenu->setCurrentSelection(arrowImage.optionSelected);
	  soundMenu->setNumberOfPlayers(numberOfPlayers);
	  soundMenu->setIsRunning(gameCore->getIsRunning());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *soundMenu );
	  arrowImage.optionSelected = soundMenu->getCurrentSelection();

	  gameCore->setIsRunning(soundMenu->getIsRunning());

	  if ( soundMenu->getNewIdGameState() != getNameState() )
	  {
		setHasEnded( soundMenu->getNewIdGameState() );
		return;
	  }
	}
  }

  for (std::string::size_type i = 0; i < guiSoundMenu->getListBars().size(); i++)
  {
    guiSoundMenu->getListBars().at(i).updateCurrentBarFrame();
  } 

  arrowImage.updatePositionArrow();
}

void SSoundOptions::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  for (std::string::size_type i = 0; i < guiSoundMenu->getListStaticImages().size(); i++)
  {
    gameRender->drawFullTexture(guiSoundMenu->getTexturesStaticImages().at(i), 
		                        guiSoundMenu->getListStaticImages().at(i).getPosition(),
                                guiSoundMenu->getListStaticImages().at(i).getOffset().x, 
								guiSoundMenu->getListStaticImages().at(i).getOffset().y);
  }

  for (std::string::size_type i = 0; i < guiSoundMenu->getListButtons().size(); i++)
  {
    gameRender->drawButton(guiSoundMenu->getTextureButtons(),
		                   guiSoundMenu->getListButtons().at(i).getPosition(),
		                   guiSoundMenu->getListButtons().at(i).getDimensions(),
		                   guiSoundMenu->getListButtons().at(i).getTexturePosition());
  }

  for (std::string::size_type i = 0; i < guiSoundMenu->getListBars().size(); i++)
  {
    guiSoundMenu->getListBars().at(i).draw();
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

void SSoundOptions::cleanUp()
{
  controllers.clear();

  delete arrowImage.arrow;
  delete customCursor.cursor;

  delete guiSoundMenu;
  delete soundMenu;
  delete timer;
}

void SSoundOptions::createGUI()
{
  RPRGUI::GUIManager* guiManager = gameRender->getGUIManager();
  std::string commonPath = "Resources/Menus/Sound Menu/";

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

  arrowImage.arrow = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(530.0f, 64.0f), 
                                    Vector2f(0.0f, 0.0f), commonPath + "SoundMenuHighlighter.png");
  arrowImage.optionSelected = MenuData::NOTHING_SELECTED;

  customCursor.cursor = new Image::GameImage(Vector2f(0.0f, 0.0f), Vector2f(64.0f, 64.0f), 
                                             Vector2f(0.0f, 0.0f), "Resources/GUI/Cursor.png");  

  guiSoundMenu->addStaticImage( guiManager->createStaticImage(Vector2f(0.0f, 0.0f),
	                                                         Vector2f(1280.0f, 720.0f),
															 Vector2f(0.0f, 0.0f),
															 "") );
  guiSoundMenu->addTextureStaticImages(gameRender->loadTexture(commonPath + "SoundMenuBackground.png")); 

  guiSoundMenu->addButton( guiManager->createButton(MenuData::EFFECTS, Vector2f(410.0f, 280.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 0.0f),
	                                               MainStates::STATE_SOUNDS_OPTIONS) );
  guiSoundMenu->addButton( guiManager->createButton(MenuData::MUSIC, Vector2f(387.0f, 380.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 32.0f),
	                                               MainStates::STATE_SOUNDS_OPTIONS) );
  guiSoundMenu->addButton( guiManager->createButton(MenuData::BACK_PAUSE, Vector2f(510.0f, 480.0f), 
	                                               Vector2f(256.0f, 32.0f), Vector2f(0.0f, 64.0f),
	                                               MainStates::STATE_PAUSE) );

  guiSoundMenu->addTextureButtons( gameRender->loadTexture(commonPath + "SoundMenuButtons.png") );  

  guiSoundMenu->addBar( new RPRGUI::SoundBar(MenuData::EFFECTS, commonPath + "SoundLevel.png") );
  guiSoundMenu->addBar( new RPRGUI::SoundBar(MenuData::MUSIC, commonPath + "SoundLevel.png") );

  for (std::string::size_type i = 0; i < guiSoundMenu->getListBars().size(); i++)
  {
    guiSoundMenu->getListBars().at(i).updateCurrentBarFrame();
  } 
}

void SSoundOptions::handleMouseUp(Uint8 button, Vector2f mousePosition)
{
  switch ( button )
  {
    case SDL_BUTTON_LEFT:
    {
      arrowImage.optionSelected = guiSoundMenu->checkMousePosition(mousePosition);
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

void SSoundOptions::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                                 std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  const int UP = -1;
  const int DOWN = 1;

  bool moveUp = inputs.actions.find(GameCoreStates::UP) != inputs.actions.end();
  bool moveDown = inputs.actions.find(GameCoreStates::DOWN) != inputs.actions.end();
  bool increaseVolume = inputs.actions.find(GameCoreStates::RIGHT) != inputs.actions.end();
  bool decreaseVolume = inputs.actions.find(GameCoreStates::LEFT) != inputs.actions.end();
  bool pressedButton = inputs.actions.find(GameCoreStates::CONTINUE) != inputs.actions.end();
  bool back = inputs.actions.find(GameCoreStates::BACK) != inputs.actions.end();

  if ( moveUp )
  {
	GameSound::getInstance()->playAdditionalChunk(4, 1, 1);
    if ( menu.getCurrentSelection() - 1 == MenuData::NOTHING_SELECTED ||
		 menu.getCurrentSelection() == MenuData::NOTHING_SELECTED)
    {
	  menu.setCurrentSelection(MenuData::BACK_PAUSE);
	}
	else
	{
	  menu.moveSelection(UP);
	}
  }

  if ( moveDown )
  {
	  GameSound::getInstance()->playAdditionalChunk(4, 1, 1);
    if ( menu.getCurrentSelection() + 1 > MenuData::BACK_PAUSE )
    {
	  menu.setCurrentSelection(MenuData::MUSIC);
    }
	else
	{
      menu.moveSelection(DOWN);
	}
  }

  if ( increaseVolume )
  {
    if ( menu.getCurrentSelection() == MenuData::EFFECTS )
    {
	  GameSound::getInstance()->upEffectsVolume(0.1f);
    }

    if ( menu.getCurrentSelection() == MenuData::MUSIC )
    {
      GameSound::getInstance()->upMusicVolume(0.1f);
    }
  }

  if ( decreaseVolume )
  {
    if ( menu.getCurrentSelection() == MenuData::EFFECTS )
    {
	  GameSound::getInstance()->downEffectsVolume(0.1f);
    }

    if ( menu.getCurrentSelection() == MenuData::MUSIC )
    {
      GameSound::getInstance()->downMusicVolume(0.1f);
    }
  }

  if ( pressedButton )
  {
	bool running = menu.getIsRunning();
	int gameMode = 0;
	if ( menu.getCurrentSelection() != MenuData::NOTHING_SELECTED )
    {
	  menu.setNewIdGameState( menu.getListButtons().at( menu.getCurrentSelection() - 1 ).eventClicked(&running, &gameMode) );
    }
	menu.setIsRunning(running);
  }

  if ( back )
  {
	  GameSound::getInstance()->clearAuxiliarSystem();
      menu.setNewIdGameState(MainStates::STATE_PAUSE);
  }
}