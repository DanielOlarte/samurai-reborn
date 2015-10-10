#pragma once

#include "Controller.h"

#include <SDL\SDL.h>

namespace InputMapping
{
  class Keyboard : public Controller
  {
    public:
	 Keyboard(int id, std::string context);

	 void parseRawInput(Key& key, InputMapping::MappedInput& inputs);
	 Key getKeyDirectionX(int directionX);
	 void updateStateKeys(InputMapping::MappedInput& inputs);

	 bool checkKeyState(Uint8 key);
  };
}

