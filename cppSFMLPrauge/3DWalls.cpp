#include "mimosdono/3DWalls.h"

namespace walls
{
	Point::Point()
	{
		elevation = 0;
	}

	Point::Point(float e)
	{
		elevation = e;
	}

	std::string Stick::posKey()
	{
		return "" + std::to_string((int)(x)) + ',' + std::to_string((int)(y));
	}
}