#include "mimosdono/JacksObjects.h"

namespace objs
{
	DroppedItem::DroppedItem(float ax, float ay, int i)
	{
		markedForDeletion = false;
		name = "";
		width = 0;
		height = 0;
		elevation = 0;
		PI = 3.1415926535f;
		angle = 0;
		x1 = 0;
		y1 = 0;
		r = 5;
		timeStarted = 0;
		speedX = ((float)std::rand() / RAND_MAX) * 5 - 2;
		speedY = ((float)std::rand() / RAND_MAX) * 5 - 2;
		yTravel = 0;
		maxYTravel = ((float)std::rand() / RAND_MAX) * 7;
		thing = "";
		x = ax;
		y = ay;
		id = i;
	};
	void DroppedItem::update()
	{
		x += speedX / 4;
		speedX *= .95;
		if (std::abs(yTravel) < maxYTravel)
		{
			y += speedY / 4;
			yTravel += speedY / 4;
		}
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		angle = (int)((t1.time_since_epoch().count() + timeStarted) / 1500000) % 360;
		x1 = r * std::cos(angle * PI / 180);
		y1 = r * std::sin(angle * PI / 180);
		elevation = y1 / 3;
	}
	bool operator==(const DroppedItem& a, const DroppedItem& b)
	{
		if (a.id == b.id)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}