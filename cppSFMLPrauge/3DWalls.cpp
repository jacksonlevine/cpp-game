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

	bool Stick::operator==(const Stick& other)
	{
		if (other.id == this->id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}