
#include "GameInputContext.h"
#include "File.h"

InputMapping::Key::Key(InputMapping::RawInputButton buttonValue, bool pressed, bool released, 
                       bool previously)
{
  button = buttonValue;	
  isPressed = pressed;
  isReleased = released;
  wasPreviouslyPressed = previously; 
}

InputMapping::Key::Key()
{
}

InputMapping::GameInputContext::GameInputContext(const std::string filename)
{
  std::ifstream inputContextFile(filename.c_str());

  unsigned stateCount = readDataTypeFromFile<unsigned>(inputContextFile);
  for(unsigned i = 0; i < stateCount; i++)
  {
    RawInputButton button = static_cast<RawInputButton>(readDataTypeFromFile<unsigned>(inputContextFile));
    Key newKey = Key(button, false, false, false);
    keysList.push_back(newKey);
    GameCoreStates::SpriteState state = static_cast<GameCoreStates::SpriteState>(readDataTypeFromFile<unsigned>(inputContextFile));
    stateMap[button] = state;
  }

  unsigned actionCount = readDataTypeFromFile<unsigned>(inputContextFile);
  for(unsigned i = 0; i < actionCount; i++)
  {
    RawInputButton button = static_cast<RawInputButton>(readDataTypeFromFile<unsigned>(inputContextFile));
    Key newKey = Key(button, false, false, false);
    keysList.push_back(newKey);
    GameCoreStates::Action action = static_cast<GameCoreStates::Action>(readDataTypeFromFile<unsigned>(inputContextFile));
    actionMap[button] = action;
  }
}

InputMapping::GameInputContext::~GameInputContext(void)
{
  actionMap.clear();
  stateMap.clear();
  keysList.clear();
}

bool InputMapping::GameInputContext::mapButtonToAction(InputMapping::RawInputButton button, 
                                                       GameCoreStates::Action& outActiveAction) const
{
  std::map<RawInputButton, GameCoreStates::Action>::const_iterator iter = actionMap.find(button);
  
  if( iter == actionMap.end() )
  {
    return false;
  }

  outActiveAction = iter->second;
  return true;
}

bool InputMapping::GameInputContext::mapButtonToState(InputMapping::RawInputButton button, 
                                                      GameCoreStates::SpriteState& outActiveState) const
{
  std::map<RawInputButton, GameCoreStates::SpriteState>::const_iterator iter = stateMap.find(button);

  if( iter == stateMap.end() )
  {
    return false;
  }

  outActiveState = iter->second;
  return true;
}

