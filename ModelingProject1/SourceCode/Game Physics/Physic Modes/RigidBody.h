#pragma once

#include "PhysicsCore.h"

#include <GameInputContext.h>
#include <PlayerState.h>

namespace GamePhysics
{
  class RigidBody : public PhysicsCore
  {
    public:
     RigidBody(int mode);
     ~RigidBody(void);

     void initializeNaturalPhysicsForces(float forceOne, float forceTwo);
	 void initializeSpeedVectors(std::vector< Vector2f > maxSpeed);
     void applyNaturalPhysicForces(int currentMovement, GLfloat* speedX, GLfloat* speedY, int playerState, int direction, 
		                           int previousState);
	 
	 GLfloat getMomentumForce(GLfloat momentumValue, GLfloat speedX, int axisDirection);
	 void setAccelerationState(int state) { accState = (AccelerationState)state; }

	 bool updateAccelerationState(std::list<InputMapping::Key> keys, GameCoreStates::ConditionsPlayerRunning isPacing, 
		                          GLfloat speedX, int currentState, int idNewState, int directionX);

	 std::vector< Vector2f > getMaxSpeed() { return maxSpeed; }

    private:
     float gravityValue;
     float accelerationXValue;

	 AccelerationState accState;

	 std::vector< Vector2f > maxSpeed;

     void parabolicShot(GLfloat* yVelocity, int playerState);
	 void acceleratePlayer(GLfloat* xVelocity, int playerState, int previousState, int directionX);
  };
}
