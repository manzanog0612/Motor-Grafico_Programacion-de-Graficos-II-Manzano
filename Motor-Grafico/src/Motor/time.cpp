#include "time.h"

namespace engine
{
	time::time()
	{

	}
	time::~time()
	{

	}
	float time::getDeltaTime()
	{
		return currentDeltaTime;
	}
	void time::updateDeltaTime(float currentTime)
	{
		currentDeltaTime = currentTime - lastDeltaTime;
		lastDeltaTime = currentTime;
	}
	float time::currentDeltaTime = 0;
	float time::lastDeltaTime = 0;
}