
#include <algorithm>
#include <fstream>

#include "SpriteDataConstants.h"
#include "GameInputMapper.h"
#include "GameInputContext.h"
#include "File.h"

InputMapping::GameInputMapper::GameInputMapper(std::string filename)
{
  unsigned countContexts;
    
  std::ifstream inputContextFile(filename);
  countContexts = readDataTypeFromFile<unsigned>(inputContextFile);

  for(unsigned i = 0; i < countContexts; i++)
  {
    std::string name = readDataTypeFromFile<std::string>(inputContextFile);
    std::string file = readDataTypeFromFile<std::string>(inputContextFile);
    inputContexts[name] = new GameInputContext(file);
  }

  currentMappedInput.buttonPreviouslyPressed = InputMapping::RAW_INPUT_NO_BUTTON;
  currentMappedInput.directionKeyPressed = SpriteData::RIGHT;
}

InputMapping::GameInputMapper::~GameInputMapper()
{
  for(std::map<std::string, GameInputContext*>::iterator iter = inputContexts.begin(); 
                                                        iter != inputContexts.end(); iter++)
  {
    delete iter->second;
  }
}

void InputMapping::GameInputMapper::clearCurrentMappedInput(GameCoreStates::SpriteState activeState)
{
  currentMappedInput.actions.clear();

  if ( !currentMappedInput.states.empty() )
  {
    if (activeState == GameCoreStates::DOUBLE_JUMP || activeState == GameCoreStates::FALLING)
    {
      activeState = GameCoreStates::JUMPING;
    }

    currentMappedInput.states.clear();
    currentMappedInput.states.push_back(activeState);
  }
}

void InputMapping::GameInputMapper::addCallback(inputCallback callback, int priorityInMultimap)
{
  callbackTable.insert(std::make_pair(priorityInMultimap, callback));
}

void InputMapping::GameInputMapper::dispatchInput(Characters::Player& player, std::list<Key>& keys, 
	                                              Image::MenuSelection& menu) const
{
  MappedInput input = currentMappedInput;

  for(std::multimap<int, inputCallback>::const_iterator iter = callbackTable.begin(); 
                                                        iter != callbackTable.end(); iter++)
  {
    (*iter->second)(input, player, keys, menu);
  }
}

void InputMapping::GameInputMapper::pushContext(const std::string& name)
{
  std::map<std::string, GameInputContext*>::iterator iter = inputContexts.find(name);
  if( iter == inputContexts.end() )
  {
    throw std::exception("Invalid Input Context Pushed To List");
  }

  activeContexts.push_front(iter->second);
}

void InputMapping::GameInputMapper::popContext()
{
  if(activeContexts.empty())
  {
    throw std::exception("Cannot Pop Input Context Because There Is Not An Active Contexts");
  }

  activeContexts.pop_front();
}

void InputMapping::GameInputMapper::processNewInput(InputMapping::Controller& controller)
{
  controller.updateStateKeys(currentMappedInput);
}

std::list<InputMapping::Key> InputMapping::GameInputMapper::getListKeys() const
{
  InputMapping::GameInputContext* gameInputActualContext = activeContexts.front();
  return *gameInputActualContext->getKeysList();
}

std::map<InputMapping::RawInputButton, GameCoreStates::Action> InputMapping::GameInputMapper::getActionMap() const
{
  InputMapping::GameInputContext* gameInputActualContext = activeContexts.front();
  return *gameInputActualContext->getActionMap();
}

std::map<InputMapping::RawInputButton, GameCoreStates::SpriteState> InputMapping::GameInputMapper::getStateMap() const
{
  InputMapping::GameInputContext* gameInputActualContext = activeContexts.front();
  return *gameInputActualContext->getStateMap();
}

void InputMapping::GameInputMapper::pushBackStateOnMappedInput(GameCoreStates::SpriteState newState)
{
  currentMappedInput.states.push_back(newState);
}

void InputMapping::GameInputMapper::pushBackActionOnMappedInput(GameCoreStates::Action newAction)
{
  currentMappedInput.actions.insert(newAction);
}

bool InputMapping::GameInputMapper::mapButtonToAction(InputMapping::RawInputButton button, 
                                                     GameCoreStates::Action& action) const
{
  for(std::list<GameInputContext*>::const_iterator iter = activeContexts.begin(); iter != activeContexts.end(); iter++)
  {
    const GameInputContext* context = *iter;

    if( context->mapButtonToAction(button, action) )
    {
      return true;
    }
  }

  return false;
}

bool InputMapping::GameInputMapper::mapButtonToState(InputMapping::RawInputButton button, 
                                                    GameCoreStates::SpriteState& state) const
{
  for(std::list<GameInputContext*>::const_iterator iter = activeContexts.begin(); iter != activeContexts.end(); iter++)
  {
    const GameInputContext* context = *iter;

    if( context->mapButtonToState(button, state) )
    {
      return true;
    }
  }

  return false;
}