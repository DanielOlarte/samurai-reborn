#pragma once

#include <windows.h>
#include <gl\GL.h>

namespace RPRGUI
{
  class Bar
  {
    public:
	 Bar() { value = 0; }

	 virtual void draw() { };

	 int getID() { return id; }

	 int getValue() { return value; }

	 virtual void updateCurrentBarFrame() { };

    protected:
	 int id;
     int value;
  };
}