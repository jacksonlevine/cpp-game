#include "mimosdono/JacksObjects.h"

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