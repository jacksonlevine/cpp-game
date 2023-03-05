#include "mimosdono/JacksObjects.h"

namespace objs
{
	float getRandom()
	{
		return (float)std::rand() / RAND_MAX;
	}
	int clamp(int val, int min, int max)
	{
		return std::min(std::max(val, min), max);
	}
}