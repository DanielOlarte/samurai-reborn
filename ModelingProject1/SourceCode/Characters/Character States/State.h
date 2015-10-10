#pragma once

class State
{
 public:
  State(){};
  virtual ~State(){};

  int getCurrentID() { return currentID; }
    
 protected:
  State(int id);
  int currentID;
};
