#pragma once

#include <windows.h>
#include <GL/gl.h>

struct Vector2f
{
  GLfloat x, y;

  Vector2f(GLfloat pointX, GLfloat pointY) 
  {
    x = pointX;	
    y = pointY; 
  }

  Vector2f()
  {
    x = y = 0;
  }
};

struct Vector2i
{
  int x, y;

  Vector2i(int pointX, int pointY) 
  {
    x = pointX;	
    y = pointY; 
  }

  Vector2i()
  {
    x = y = 0;
  }
};
