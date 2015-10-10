#pragma once

#include "Controller.h"

#include <Xinput.h>

namespace InputMapping
{
  class Gamepad : public Controller
  {
    public:
	 Gamepad(int id, std::string context);

	 bool isEnabled();

	 void parseRawInput(Key& key, InputMapping::MappedInput& inputs);
	 Key getKeyDirectionX(int directionX);
	 void updateStateKeys(InputMapping::MappedInput& inputs);

	 bool isWalkingLeftPressed(Key key);
	 bool isWalkingRightPressed(Key key);

	 bool checkKeyState(WORD button);
  };
}

