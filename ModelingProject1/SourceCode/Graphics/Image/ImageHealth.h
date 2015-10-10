#pragma once

#include <ImageObject.h>

namespace Image
{
  class ImageHealth : public ImageObject
  {
   public:
	ImageHealth(Vector2f imagePosition, Vector2f imageOffset, Vector2f texturePosition, int max);

	int getMaxAmount() { return maxAmount; }

	int getCurrentAmount() { return currentAmount; }

	void setCurrentAmount(int current) { currentAmount = current; }

   private:
    int maxAmount;
	int currentAmount;
  };
}