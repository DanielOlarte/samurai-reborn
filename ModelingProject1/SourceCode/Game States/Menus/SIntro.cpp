#include "SIntro.h"

const int LOGO_COMPANY = 0;
const int LOGO_GAME = 1;
const int NO_LOGO = 2;

SIntro::SIntro(GameRender* gR, GameCore* gC, GameInput* gI, MainStates::GameStates stateName) 
    : GameState( gR, gC, gI, stateName )
{
  gameCore = gC;
  gameRender = gR;
  gameInput = gI;
  nameState = stateName;

  timer = new GameTimer();
  timer->setFramesPerSecond(30);

  setHasEnded(MainStates::STATE_INTRO);
  setProperty(MainStates::NORMAL_MENU);

  currentLogo = LOGO_COMPANY;
}

SIntro::~SIntro(void)
{
}

void SIntro::init()
{
  std::string commonPath = "Resources/Menus/Intro/";
  logos.push_back( new Image::GameImage( Vector2f(0.0f, 0.0f), 
	                                     Vector2f(1280.0f, 720.0f),
                                         Vector2f(0.0f, 0.0f), 
								         commonPath + "LogoBrainstormInteractive.png" ) );
  logos.push_back( new Image::GameImage( Vector2f(0.0f, 0.0f), 
	                                    Vector2f(1280.0f, 720.0f),
                                        Vector2f(0.0f, 0.0f), 
										commonPath + "LogoSamuraiReborn.png" ) );
}

void SIntro::handleEvents()
{
  bool isRunning = gameInput->handleWindowEvents();
  gameCore->setIsRunning( isRunning );
}

void SIntro::logic()
{
}

void SIntro::render()
{
  glClear( GL_COLOR_BUFFER_BIT );

  gameRender->drawFullTexture(logos.at(currentLogo).getTexture(), logos.at(currentLogo).getPosition(),
                              logos.at(currentLogo).getOffset().x, logos.at(currentLogo).getOffset().y);

  SDL_GL_SwapBuffers();

  Uint32 startTime = SDL_GetTicks();
  while(SDL_GetTicks() - startTime < 3000)
  {
  }
  currentLogo += 1;

  if ( currentLogo == NO_LOGO )
  {
	setHasEnded(MainStates::STATE_MAINMENU);
  }
}

void SIntro::cleanUp()
{
  logos.clear();
}
