#pragma once

#include <windows.h>
#include <GL/gl.h>

#include <vector>

#include "PhysicModes.h"
#include "Vector.h"

namespace GamePhysics
{
  class PhysicsCore
  {
    public:
     PhysicsCore(int mode);
     ~PhysicsCore(void);
    
     virtual void initializeNaturalPhysicsForces(float forceOne, float forceTwo) = 0;
	 virtual void initializeSpeedVectors(std::vector< Vector2f > maxSpeed) = 0;
     virtual void applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, 
                                           int playerState, int direction, int previousState) = 0;

    protected:
     PhysicModes nameMode;
  };
}
