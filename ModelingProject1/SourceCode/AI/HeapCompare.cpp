
#include "HeapCompare.h"

AISystem::HeapCompare::HeapCompare(void)
{
}

AISystem::HeapCompare::~HeapCompare(void)
{
}

bool AISystem::HeapCompare::operator() ( const PathNode* x, const PathNode* y ) const
{
  return x->scoreFunction < y->scoreFunction;
}
