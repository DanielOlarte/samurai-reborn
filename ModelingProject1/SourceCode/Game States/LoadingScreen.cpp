
#include "LoadingScreen.h"

LoadingScreen::LoadingScreen(std::string nameLevel)
{
  statusBarWidth = 614;
  statusBarPosition = Vector2f(333.f, 468.f);
  statusBarOffset = Vector2f(19.f, 46.f);

  std::string commonPath = "Resources/Menus/Loading State/";

  statusBarUnit = GameRender::loadTexture(commonPath + "LoadingBar.png");
  background = GameRender::loadTexture(commonPath + "LoadingState.png");
  levelScreen = GameRender::loadTexture(commonPath + nameLevel + ".png");
}

LoadingScreen::~LoadingScreen(void)
{
  glDeleteTextures(1, &background);
  glDeleteTextures(1, &statusBarUnit);
  glDeleteTextures(1, &levelScreen);
}

void LoadingScreen::updateValues(int percentage)
{
  renderScreen(percentage);
}

void LoadingScreen::renderScreen(int percentage)
{
  glClear( GL_COLOR_BUFFER_BIT );

  GameRender::drawFullTexture(background, Vector2f(0,0), 1280.f, 720.f);
  GameRender::drawFullTexture(statusBarUnit, statusBarPosition, statusBarWidth*percentage/100, statusBarOffset.y);
  GameRender::drawFullTexture(levelScreen, Vector2f(358.0f, 129.0f), 549.0f, 297.0f);
	
  SDL_GL_SwapBuffers();
  if( percentage == 100 )
  {
    Uint32 startTime = SDL_GetTicks();
    while(SDL_GetTicks() - startTime < 500)
	{
    }
  }
}