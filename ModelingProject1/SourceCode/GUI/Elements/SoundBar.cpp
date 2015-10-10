
#include <SoundBar.h>

#include <GameRender.h>
#include <MenuData.h>

#include <GameSound.h>

RPRGUI::SoundBar::SoundBar(int id, std::string filename)
{
  this->id = id;
  textureBar = GameRender::loadTexture(filename);

  position = Vector2f( 730.0f, 245.0f + ((id-1)*100.0f) );
  imageDimensions = Vector2f( 18.0f, 80.0f );

  currentBarFrame = 4;
  maxBarFrames = 5;
}

RPRGUI::SoundBar::~SoundBar()
{
  glDeleteTextures(1, &textureBar);
}

void RPRGUI::SoundBar::draw()
{
  GameRender::drawSoundBar(textureBar, position, imageDimensions, maxBarFrames, MenuData::EMPTY);
  GameRender::drawSoundBar(textureBar, position, imageDimensions, currentBarFrame, MenuData::TO_FULLFILL);
}

void RPRGUI::SoundBar::updateCurrentBarFrame()
{
  int amountOfBars = 0;
  float volume = 0.0f;
  switch(id)
  {
    case MenuData::EFFECTS:
	{
	  volume = GameSound::getInstance()->getEffectsVolume();
	  break;
	}
    case MenuData::MUSIC:
    {
	  volume = GameSound::getInstance()->getMusicVolume();
      break;
    }
  }

  for ( int i = 0; i < maxBarFrames; i++)
  {
	if ( volume > 0.20f*i )
	{
	  amountOfBars  += 1;
	}
  }

  currentBarFrame = amountOfBars;
}