#include "mimosdono/JacksObjects.h"

namespace objs
{
	FixedObject::FixedObject()
	{
		width = 0;
		height = 0;
		type = 0;
		x = 0;
		y = 0;
		strength = 10;
	};
	FixedObject::FixedObject(std::string thi, int wi, int he, int ty)
	{
		x = 0;
		y = 0;
		strength = 10;
		thing = thi;
		width = wi;
		height = he;
		type = ty;
	}
	void FixedObject::clickEvent()
	{
		strength -= 1;
	}
}
	