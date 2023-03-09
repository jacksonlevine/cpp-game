#include "mimosdono/JacksObjects.h"
#include "mimosdono/Game.h"

namespace objs
{
	Player::Player()
	{
		name = "";
		inv = Inventory();
		x = 0;
		y = 0;
		width = 3;
		height = 3;
		jump = false;
		elevation = 0;
		gravityForce = 0;
		jumpForce = 20;
		left = false;
		right = false;
		up = false;
		down = false;
		movementSpeed = 1.2;
	};
	Player::Player(std::string pname, int px, int py)
	{
		name = pname;
		x = px;
		y = py;
		inv = Inventory();
		width = 3;
		height = 3;
		jump = false;
		elevation = 0;
		gravityForce = 0;
		jumpForce = 20;
		left = false;
		right = false;
		up = false;
		down = false;
		movementSpeed = 1.2;
	};
	Player::Player(std::string pname, int px, int py, int wid, int hei)
	{
		name = pname;
		x = px;
		y = py;
		inv = Inventory();
		width = wid;
		height = hei;
		jump = false;
		elevation = 0;
		gravityForce = 0;
		jumpForce = 20;
		left = false;
		right = false;
		up = false;
		down = false;
		movementSpeed = 1.2;
	};
	std::string Player::posKey()
	{
		return "" + std::to_string((int)(x)) + ',' + std::to_string((int)(y));
	}
	void Player::move(float mx, float my, std::unordered_map<std::string, Player*>* pmap)
	{
		pmap->erase(posKey());
		x += mx;
		y += my;
		pmap->insert_or_assign(posKey(), this);
	}
	void Player::stepJump()
	{
		if (jump == true)
		{
			if (elevation >= 0)
			{
				elevation += (jumpForce - gravityForce);
				gravityForce += 1.6;
			}
			else
			{
				jump = false;
				gravityForce = 0;
				elevation = 0;
			}
		}
	}
}

namespace jl
{
	void Game::addPlayerPixelsToBuffer(int floorX, int floorY, std::unordered_map<std::string, objs::PlayerPixel>& screenumap)
	{
		std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
		if (pmap.find(keySpot) != pmap.end())
		{
			int yoff = 0;
			int yshrink = 0;
			if (worldmap.find(keySpot) != worldmap.end())
			{
				yoff = std::floor(worldmap.at(keySpot).elevation);
			}
			else
			{
				yshrink = 2;
			}
			int elevOs = std::floor((int)pmap.at(keySpot)->elevation >> 4);
			if (pmap.at(keySpot)->jump == true)
			{
				pmap.at(keySpot)->stepJump();
			}
			for (int a = 0 + yoff + std::max(yshrink - elevOs, 0) + elevOs; a < pmap.at(keySpot)->height + yoff + elevOs; a++)
			{
				for (int l = 0; l < pmap.at(keySpot)->width; l++)
				{
					sf::Color col;
					col.r = 255;
					col.g = 0;
					col.b = 0;
					col.a = 255;
					std::string thisKeySpot = "" + std::to_string(floorX + l) + ',' + std::to_string(floorY - a);
					objs::PlayerPixel pp(col, (int)(pmap.at(keySpot)->x), (int)(pmap.at(keySpot)->y));
					screenumap[thisKeySpot] = pp;
				}
			}
		}
	}
}