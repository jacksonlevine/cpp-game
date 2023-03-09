#include "mimosdono/JacksObjects.h"
#include "mimosdono/Game.h"
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

namespace jl
{
	void Game::updateDropsAndAddToScreenBuffer(std::unordered_map<std::string, objs::PlayerPixel>& screenumap)
	{
		int dCount = drops.size();
		for (int i = 0; i < dCount; i++)
		{
			drops[i].update();
			int range = 20;
			if (std::abs(drops[i].x - play.x) < range && std::abs(drops[i].y - play.y) < range)
			{
				drops[i].x += (play.x - drops[i].x) / 10;
				drops[i].y += (play.y - drops[i].y) / 10;
				if (std::abs(drops[i].x - play.x) < 1 && std::abs(drops[i].y - play.y) < 1)
				{
					if (typeID.find(drops[i].name) != typeID.end())
					{
						int found = play.inv.findItem(typeID.at(drops[i].name));
						int fos = play.inv.firstOpenSlot();
						if (found != -1)
						{
							play.inv.inv[found].count += 1;
						}
						else if (fos != -1)
						{
							play.inv.inv[fos].id = typeID.at(drops[i].name);
							play.inv.inv[fos].count = 1;
							play.inv.inv[fos].thing = drops[i].thing;
							play.inv.inv[fos].thingWidth = drops[i].width;
							play.inv.inv[fos].thingHeight = drops[i].height;
						}
						if (found != -1 || fos != -1)
						{
							drops[i].markedForDeletion = true;
						}
					}
				}
			}
			int wi = drops[i].width;
			int he = drops[i].height;
			for (int h = 0; h < he; h++)
			{
				for (int w = 0; w < wi; w++)
				{
					std::string thisKeySpot = "" + std::to_string((int)(drops[i].x + w)) + ',' + std::to_string((int)((float)drops[i].y + h + ((float)drops[i].elevation)));
					sf::Color c = opixref[drops[i].thing[objs::clamp((h * wi) + w, 0, drops[i].thing.size() - 1)]];
					objs::PlayerPixel pi(c, drops[i].x + w, drops[i].y + h);
					if (drops[i].thing[objs::clamp((h * wi) + w, 0, drops[i].thing.size() - 1)] != '0')
					{
						screenumap[thisKeySpot] = pi;
					}
				}
			}
			if (drops[i].markedForDeletion == true)
			{
				std::erase(drops, drops[i]);
			}
		}
	}
}