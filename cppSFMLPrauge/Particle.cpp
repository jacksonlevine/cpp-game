#include "mimosdono/JacksObjects.h"
#include "mimosdono/Game.h"

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

namespace jl
{
	void Game::drawAndUpdateParticles()
	{
		int pCount = parts.size();
		for (int i = 0; i < pCount; i++)
		{
			parts[i].update();
			rect.setPosition(sf::Vector2f((parts[i].x - camX) * ts, (parts[i].y - camY) * ts));
			rect.setFillColor(parts[i].col);
			window.draw(rect);
			if (parts[i].timer > parts[i].life)
			{
				parts.erase(std::remove(parts.begin(), parts.end(), parts[i]), parts.end());
			}
		}
	}
}