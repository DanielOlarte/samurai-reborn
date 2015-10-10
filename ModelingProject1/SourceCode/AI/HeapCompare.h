#pragma once

#include "PathNode.h"

namespace AISystem
{
  class HeapCompare
  {
    public:
     HeapCompare(void);
     ~HeapCompare(void);

     bool operator() ( const PathNode* x, const PathNode* y ) const;
  };
}
