#pragma once

#include <string>
#include <vector>
#include <fmod.hpp>
#include <fmod_errors.h>
#include <PlayerSpriteStates.h>
#include <File.h>

/* **ID's**
SoundID: 
	0 = characterSound
	1 = Menu/LevelSound
StateID: 
	0 = attackSound
	1 = groundhitSound
	2 = runningSound
	3 = Still Attack Sound
**Files Layout**
Musics.txt:
	0 = Panda sounds
	1 = Meerkat Sounds
LevelSounds.txt:
	0 = Level One
	1 = SMainMenu
		0 = Background Music 
		1 = Selection sound
	2 = SPlayerSelection
		0 = Background Music 
		1 = Selection sound
	3 =  PauseMenu
		0 = Background Music 
		1 = Selection sound
	4 = SoundMenu
		0 = Background Music 
		1 = Selection sound

**Channels**
Channel[0] = SE = on going sounds/music
Channel[1] = MUS = one time, multiple use sounds/chunks
Channel[2] = RS = partial duration sounds

ch[0] = Additional musics
ch[1] = Additional effects

**Volume**
Max value = 1.0f
Min Value = 0.0f
volumeValues[0] = Value for the musics volume
volumeValues[1] = Value for the effects volume

*/

class GameSound 
{
  public:
   GameSound(void);
   ~GameSound();

   static GameSound* getInstance();
   bool initSound();
   void closeAll();
   void ERRCHECK(FMOD_RESULT);
   void pauseSystem();
   void unpauseSystem();
   void clearAuxiliarSystem();

   void initSounds(int characterID, int soundType);
   void splitFileSounds(std::string line, int soundType);

   void upVolume(int channelID, float increasingValue);
   void downVolume(int channelID, float decreasingValue);
   float getVolume(int channelID);

   void upOverallVolume(float increasingValue);
   void downOverallVolume(float decreasingValue);
   void upMusicVolume(float increasingValue);
   void downMusicVolume(float decreasingValue);
   void upEffectsVolume(float increasingValue);
   void downEffectsVolume(float decreasingValue);

   void loadChunk(int row, int soundType, int soundID);
   void loadSound(int row, int soundType, int soundID);
   void playAdditionalSound(int row, int soundType, int soundID);
   void playAdditionalChunk(int row, int soundType, int soundID);
   void playSound(int row, int soundType, int soundID);
   void closeSound();

   void stateSoundsHandling(GameCoreStates::SpriteState previousState);
   std::string soundSelection(int soundType, int soundID);

   float getMusicVolume();
   float getEffectsVolume();

  private:
   std::vector< std::string > ambienceSounds;
   std::vector< std::string > statesSounds;

   std::string sFilename;
   std::string lFilename;

   static bool instanceFlag;
   const char* currentSound;
   static GameSound* gameSound;

   FMOD::System* system;
   FMOD::Sound* sound;
   FMOD::Sound* chunks[3];
   FMOD::Channel* channel[3];
   FMOD_RESULT result;

   FMOD::Sound* sd;
   FMOD::Channel* ch[2];
   FMOD::System* syste;
   FMOD_RESULT res;
   float volumeValues[2];
};