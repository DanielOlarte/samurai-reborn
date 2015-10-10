
#include "GameScreen.h"

#include <SDL/SDL_ttf.h>

GameScreen::GameScreen(void)
{
  screen = NULL;
  width = height = 0;
  windowName = "Samurai Reborn";
}

GameScreen::~GameScreen(void)
{
}

bool GameScreen::initializeScreen()
{
  if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
  {
    return false;
  }
    
  if( !initializeSDLGLState() )
  {
    return false;
  }

  SDL_putenv("SDL_VIDEO_CENTERED=center");

  width = 1280;	height = 720;

  if( (screen = SDL_SetVideoMode(width, height, 32, SDL_OPENGL /*| SDL_FULLSCREEN*/) ) == NULL) 
  {
    return false;
  }

  initializeSDLFeatures();

  if( !initializeOpenGL() )
  {
    return false;
  }

  if ( TTF_Init() < 0 )
  {
    return false;
  }

  SDL_WM_SetCaption( windowName.c_str(), NULL );

  return true;
}

bool GameScreen::initializeOpenGL()
{	
  defaultResolution = SDL_GetVideoInfo();
  float proportion = ( (float)defaultResolution->current_w / (float)defaultResolution->current_h );

  glViewport(0, 0, defaultResolution->current_w, defaultResolution->current_h);
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
        
  if(proportion > 1.5 && proportion < 1.7)
  {
    glOrtho( 0, 1280,800, 0, -1, 1 );
  }

  else if(proportion > 1.7 && proportion < 1.8)
  {
    glOrtho( 0, 1280,720, 0, -1, 1 );
  }

  else
  {
    glOrtho( 0, 1280,960, 0, -1, 1 );
  }
    
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();

  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

  if( glGetError() != GL_NO_ERROR )
  {
    return false;
  }

  return true;
}

bool GameScreen::initializeSDLGLState()
{
  if ( SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ) != 0 )
  {
    return false;
  }

  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ALPHA_SIZE, 8 );
 
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );
  SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
 
  SDL_GL_SetAttribute( SDL_GL_ACCUM_RED_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_GREEN_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_BLUE_SIZE, 8 );
  SDL_GL_SetAttribute( SDL_GL_ACCUM_ALPHA_SIZE, 8 );
 
  SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1 );
  SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 2 );

  return true;
}

void GameScreen::initializeSDLFeatures()
{
  SDL_ShowCursor( SDL_DISABLE );
  SDL_EnableUNICODE( 1 );
  SDL_EnableKeyRepeat( SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL );
}

GLfloat GameScreen::getWidth()
{
  defaultResolution = SDL_GetVideoInfo();
  return (GLfloat)defaultResolution->current_w;
}


