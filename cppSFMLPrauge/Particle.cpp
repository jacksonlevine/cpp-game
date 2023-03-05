#include "mimosdono/JacksObjects.h"

namespace objs
{
	Particle::Particle()
	{
		life = 35;
		timer = 0;
		x = 0;
		y = 0;
		col = sf::Color(0, 0, 0);
		speedX = ((float)std::rand() / RAND_MAX) * 5 - 2;
		speedY = ((float)std::rand() / RAND_MAX) * 5 - 2;
		yTravel = 0;
		maxYTravel = ((float)std::rand() / RAND_MAX) * 8;
	};
	void Particle::update()
	{
		x += speedX / 2;
		speedX *= .90;
		if (yTravel < maxYTravel)
		{
			y += speedY / 2;
			yTravel += speedY / 4;
		}
		speedY += .1;
		timer += 1;
	}
	bool operator==(const Particle& x, const Particle& y)
	{
		if (x.x == y.x && x.y == y.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}