#include "GameSound.h"

GameSound::GameSound(void)
{
  result = FMOD::System_Create(&system);
  res = FMOD::System_Create(&syste);
  printf("FMOD created");
  ERRCHECK(result);

  volumeValues[0] = 0.1f;
  volumeValues[1] = 0.2f;

  sFilename = "Game Core/Musics.txt";
  lFilename = "Game Core/LevelSounds.txt";
}

bool GameSound::instanceFlag = false;
GameSound* GameSound::gameSound = NULL;

GameSound* GameSound::getInstance()
{
  if( !instanceFlag )
  {
    gameSound = new GameSound();
    gameSound->initSound();
    instanceFlag = true;
  }
  return gameSound;
}

GameSound::~GameSound()
{
  ambienceSounds.clear();
  statesSounds.clear();
}

bool GameSound::initSound()
{
  result = system->init(32, FMOD_INIT_NORMAL, 0);
  return true;
}

void GameSound::closeSound()
{
  channel[2]->setVolume( 0.0 );
  currentSound = "NULL";
}

void GameSound::pauseSystem()
{
  FMOD::ChannelGroup* cG;
  res = syste->init(32, FMOD_INIT_NORMAL, 0);
  system->getMasterChannelGroup(&cG);
  cG->setPaused(true);
}

void GameSound::unpauseSystem()
{
  GameSound::getInstance()->clearAuxiliarSystem();
  FMOD::ChannelGroup* cG;
  system->getMasterChannelGroup(&cG);
  cG->setPaused(false);
}

void GameSound::clearAuxiliarSystem()
{
  ch[0]->setPaused(true);
  ch[1]->setPaused(true);

  ch[0]->stop();
  ch[1]->stop();

  sd->release();
  FMOD::ChannelGroup *cG1;
  syste->getMasterChannelGroup(&cG1);
  cG1->setPaused(true);
  cG1->release();
  cG1->stop();
  syste->close();
}

void GameSound::initSounds(int row, int soundType)
{
  statesSounds.clear();
  ambienceSounds.clear();
  std::string line;
  if(soundType == 0)
  {
    line = readLineFromFile(sFilename, row);
  }
  else
  {
    line = readLineFromFile(lFilename, row);
  }
  splitFileSounds(line, soundType);
}

void GameSound::splitFileSounds(std::string line, int soundType)
{
  std::string temp;

  for(std::string::size_type i = 0; i < line.size(); i++)
  {
    if( line.at(i) == ';' && temp != "" )
    {
	  if( soundType == 0 )
	  {
	    statesSounds.push_back(temp);
      }
	  else
	  {
	    ambienceSounds.push_back(temp);
	  }       
      temp = "";
    }
    else
    {
      temp += line.at(i);
    }
  }
}

void GameSound::upVolume(int channelID, float increasingValue)
{
  float volume;
  channel[channelID]->getVolume(&volume);
  volume += increasingValue;
  result = channel[channelID]->setVolume(volume);
}

void GameSound::downVolume(int channelID, float decreasingValue)
{
  float volume;
  channel[channelID]->getVolume(&volume);
  volume -= decreasingValue;
  result = channel[channelID]->setVolume(volume);
}

float GameSound::getVolume(int channelID)
{
  float volume;
  channel[channelID]->getVolume(&volume);
  return volume;
}

void GameSound::upOverallVolume(float increasingValue)
{
  FMOD::ChannelGroup* cG;
  FMOD::ChannelGroup* cG1;
  float volume;
  system->getMasterChannelGroup(&cG);

  volume = float (cG->getVolume(&volume));
  volume += increasingValue;
  result = cG->setVolume(volume);
  system->getMasterChannelGroup(&cG1);

  volume = float (cG1->getVolume(&volume));
  volume += increasingValue;
  result = cG1->setVolume(volume);
}

void GameSound::downOverallVolume(float decreasingValue)
{
  FMOD::ChannelGroup* cG;
  FMOD::ChannelGroup* cG1;
  float volume;
  system->getMasterChannelGroup(&cG);

  volume = float (cG->getVolume(&volume));
  volume -= decreasingValue;
  result = cG->setVolume(volume);

  system->getMasterChannelGroup(&cG1);
  volume = float (cG1->getVolume(&volume));
  volume -= decreasingValue;
  result = cG1->setVolume(volume);
}

void GameSound::upMusicVolume(float increasingValue)
{
  volumeValues[0] += increasingValue;
  if( volumeValues[0] >= 1.0f )
  {
    volumeValues[0] = 1.0f;
  }  
  result = channel[0]->setVolume(volumeValues[0]);
  result = ch[0]->setVolume(volumeValues[0]);
}

void GameSound::downMusicVolume(float decreasingValue)
{
  volumeValues[0] -= decreasingValue;
  if( volumeValues[0] <= 0.0f )
  {
    volumeValues[0] = 0.0f;
  }  
  result = channel[0]->setVolume(volumeValues[0]);
  result = ch[0]->setVolume(volumeValues[0]);
}

void GameSound::upEffectsVolume(float increasingValue)
{
  volumeValues[1] += increasingValue;
  if( volumeValues[1] >= 1.0f )
  {
    volumeValues[1] = 1.0f;
  }
}

void GameSound::downEffectsVolume(float decreasingValue)
{
  volumeValues[1] -= decreasingValue;
  if( volumeValues[1] <= 0.0f )
  {
    volumeValues[1] = 0.0f;
  }
}

void GameSound::loadChunk(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  name = GameSound::soundSelection(soundType, soundID);

  const char* chunkName = name.c_str();
  result = system->createSound(chunkName, FMOD_LOOP_OFF, 0, &chunks[0]);
  ERRCHECK(result);
  result = system->playSound(FMOD_CHANNEL_FREE, chunks[0], false, &channel[1]);
  ERRCHECK(result);
  channel[1]->setVolume(volumeValues[1]);
}

void GameSound::loadSound(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  name = GameSound::soundSelection(soundType, soundID);
  
  const char* musicName = name.c_str();
  printf("Loading");
  result = system->createStream(musicName, FMOD_HARDWARE | FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
  ERRCHECK(result);  
  printf("Playing");
  result = system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel[0]);
  ERRCHECK(result);
  channel[0]->setVolume(volumeValues[0]);
}

void GameSound::playAdditionalSound(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  name = GameSound::soundSelection(soundType, soundID);
                
  if( name == "none" )
  {
    return;
  }

  bool playing;
  ch[0]->isPlaying(&playing);

  if( playing == false )
  {
    currentSound = name.c_str();
    res = syste->createStream(currentSound, FMOD_DEFAULT, 0 , &sd );
    ERRCHECK(res);
    res = syste->playSound( FMOD_CHANNEL_REUSE, sd, false, &ch[0]);
    ERRCHECK(res);
    ch[0]->setVolume(volumeValues[0]);
  }
}

void GameSound::playAdditionalChunk(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  name = GameSound::soundSelection(soundType, soundID);
                
  if(name == "none")
  {
    return;
  }
  
  const char* chunkName = name.c_str();
  res = syste->createSound(chunkName, FMOD_LOOP_OFF, 0, &sd);
  ERRCHECK(res);
  
  result = syste->playSound(FMOD_CHANNEL_FREE, sd, false, &ch[1]);
  ERRCHECK(res);
  ch[1]->setVolume(volumeValues[1]);
}

void GameSound::playSound(int row, int soundType, int soundID)
{
  initSounds(row, soundType);
  std::string name;

  name = GameSound::soundSelection(soundType, soundID);
                
  if( name == "none" )
  {
    return;
  }

  currentSound = name.c_str();
  result = system->createStream( currentSound, FMOD_DEFAULT, 0, &sound );
  ERRCHECK(result);
  result = system->playSound( FMOD_CHANNEL_REUSE, sound, false, &channel[2]);
  ERRCHECK(result);
  channel[1]->setVolume(volumeValues[0]);
}

std::string GameSound::soundSelection(int soundType, int soundID)
{
  std::string name;
  if(soundType == 0)
  {
    name = statesSounds.at(soundID);
  }
  else
  {
    name = ambienceSounds.at(soundID);
  }
                
  return name;
}

void GameSound::stateSoundsHandling(GameCoreStates::SpriteState previousState)
{
  if( previousState == GameCoreStates::RUNNING )
  {
    GameSound::getInstance()->closeSound();
  }
  if( previousState == GameCoreStates::FALLING )
  {
    GameSound::getInstance()->loadChunk(0, 0, 1);
  }
}

void GameSound::closeAll()
{
  result = system->close();
  FMOD::SoundGroup *sG;
  system->getMasterSoundGroup(&sG);
  sG->stop();

  ERRCHECK(result);
  result = system->release();
  ERRCHECK(result);

  ambienceSounds.clear();
  statesSounds.clear();
  instanceFlag = false;
}

void GameSound::ERRCHECK(FMOD_RESULT result)
{
  if (result != FMOD_OK)
  {
    printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
    exit(-1);
  }
}

float GameSound::getMusicVolume()
{
  return volumeValues[0];
}

float GameSound::getEffectsVolume()
{
  return volumeValues[1];
}