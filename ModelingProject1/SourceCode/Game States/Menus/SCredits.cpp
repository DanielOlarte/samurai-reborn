
#include <SCredits.h>
#include <PandaP1.h>

SCredits::SCredits(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_CREDITS);
  setProperty(MainStates::NORMAL_MENU);
}

SCredits::~SCredits(void)
{
}

void SCredits::init()
{
  createGUI();

  menuCredits = new Image::MainMenuSelection(&controllers.at(0));
  menuCredits->setNewIdGameState(MainStates::STATE_CREDITS);
}

void SCredits::handleEvents()
{
  SDL_Event e;
  bool running = gameCore->getIsRunning();

  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {	
    controllers.at(i).getInputMapper()->clearCurrentMappedInput();
  }

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

void SCredits::logic()
{
  for (std::string::size_type i = 0; i < controllers.size(); i++)
  {
	if ( controllers.at(i).getController()->isEnabled() )
	{
	  menuCredits->setController(&controllers.at(i));
	  menuCredits->setNumberOfPlayers(numberOfPlayers);
	  menuCredits->setIsRunning(gameCore->getIsRunning());

      controllers.at(i).getInputMapper()->dispatchInput( Characters::PandaP1(),
	                                      *controllers.at(i).getController()->getListKeys(), 
										  *menuCredits );

	  gameCore->setIsRunning(menuCredits->getIsRunning());
	  gameCore->setCurrentGameMode(menuCredits->getCurrentGameMode());

	  if ( menuCredits->getNewIdGameState() != getNameState() )
	  {
		setHasEnded( menuCredits->getNewIdGameState() );
		return;
	  }
	}
  }
}

void SCredits::render()
{
  glClear( GL_COLOR_BUFFER_BIT );
  
  gameRender->drawFullTexture(background->getTexture(), background->getPosition(),
                              background->getOffset().x, background->getOffset().y);

  SDL_GL_SwapBuffers();
}

void SCredits::cleanUp()
{
  controllers.clear();
  delete background;
  delete menuCredits;
}

void SCredits::createGUI()
{
  std::string commonPath = "Resources/Menus/Credits Menu/";

  controllers.push_back( new Image::MenuController(Image::ENABLE, InputMapping::KEYBOARD) );
  controllers.at(0).setController(GameInput::initializeControllerData(getNameState(), InputMapping::KEYBOARD));
  controllers.at(0).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(0).getController(), InputMapping::KEYBOARD));
  controllers.at(0).getController()->setPlayerID(0);

  controllers.push_back( new Image::MenuController(Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(1).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(1).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(1).getController(), InputMapping::GAMEPAD));
  controllers.at(1).getController()->setPlayerID(1);

  controllers.push_back( new Image::MenuController(Image::DISABLE, InputMapping::GAMEPAD) );
  controllers.at(2).setController(GameInput::initializeControllerData(getNameState(), InputMapping::GAMEPAD));
  controllers.at(2).setGameInputMapper(GameInput::initializeGameInputMapperData(getNameState(), 
	                                   *controllers.at(2).getController(), InputMapping::GAMEPAD));
  controllers.at(2).getController()->setPlayerID(2); 

  background = new Image::GameImage( Vector2f(0.0f, 0.0f), 
	                                 Vector2f(1280.0f, 720.0f),
                                     Vector2f(0.0f, 0.0f), 
									 commonPath + "CreditsBackground.png" );
}

void SCredits::inputCallback(InputMapping::MappedInput& inputs, Characters::Player& player, 
	                         std::list<InputMapping::Key> keys, Image::MenuSelection& menu)
{
  bool backAction = inputs.actions.find(GameCoreStates::BACK) != inputs.actions.end();

  if ( backAction )
  {
    menu.setNewIdGameState(MainStates::STATE_MAINMENU);
  }
}