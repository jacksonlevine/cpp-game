#include "mimosdono/JacksObjects.h"

namespace objs
{
	ColorBrick::ColorBrick(sf::Color c, float elev)
	{
		isWater = false;
		col = c;
		elevation = elev;
	};
	ObjectBrick::ObjectBrick()
	{
		col = sf::Color(0, 0, 0);
		obx = 0;
		oby = 0;
		elevation = 0;
		point = 0;
		isReflection = false;
	};
	ObjectBrick::ObjectBrick(sf::Color c, int ox, int oy)
	{
		obx = ox;
		oby = oy;
		col = c;
		elevation = 0;
		point = 0;
		isReflection = false;
	};
	PlayerPixel::PlayerPixel()
	{
		px = 0;
		py = 0;
	};
	PlayerPixel::PlayerPixel(sf::Color c, int x, int y, bool u)
	{
		col = c;
		px = x;
		py = y;
		us = u;
	};
}