#include "mimosdono/3DWalls.h"
#include "mimosdono/Game.h"
int walls::Stick::currentId = 0;
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
	
	int Stick::assignId()
	{
		return currentId++;
	}
}
namespace jl
{
	void Game::generateWalls()
	{
		std::shared_ptr<walls::Stick> stick1(new walls::Stick);
		std::shared_ptr<walls::Stick> stick2(new walls::Stick);
		stick1->id = walls::Stick::assignId();
		stick1->bottom.elevation = 0;
		stick1->top.elevation = 2;
		stick1->primary = true;
		stick1->x = 0;
		stick1->y = 0;
		stick1->otherhalf = stick2;
		stickmap[stick1->posKey()] = *stick1.get();
		stick2->id = walls::Stick::assignId();
		stick2->bottom.elevation = 0;
		stick2->top.elevation = 2;
		stick2->primary = false;
		stick2->x = 10;
		stick2->y = 0;
		stick2->otherhalf = stick1;
		stickmap[stick2->posKey()] = *stick2.get();


		std::shared_ptr<walls::Stick> stick4(new walls::Stick);

		stick4->id = walls::Stick::assignId();
		stick4->bottom.elevation = 0;
		stick4->top.elevation = 2;
		stick4->primary = true;
		stick4->x = -5;
		stick4->y = -20;
		stick4->otherhalf = stick1;
		stickmap[stick4->posKey()] = *stick4.get();

		std::shared_ptr<walls::Stick> stick5(new walls::Stick);

		stick5->id = walls::Stick::assignId();
		stick5->bottom.elevation = 0;
		stick5->top.elevation = 2;
		stick5->primary = true;
		stick5->x = 30;
		stick5->y = -20;
		stick5->otherhalf = stick4;
		stickmap[stick5->posKey()] = *stick5.get();

		std::shared_ptr<walls::Stick> stick6(new walls::Stick);

		stick6->id = walls::Stick::assignId();
		stick6->bottom.elevation = 0;
		stick6->top.elevation = 2;
		stick6->primary = true;
		stick6->x = 37;
		stick6->y = -27;
		stick6->otherhalf = stick5;
		stickmap[stick6->posKey()] = *stick6.get();

		std::shared_ptr<walls::Stick> stick7(new walls::Stick);

		stick7->id = walls::Stick::assignId();
		stick7->bottom.elevation = 0;
		stick7->top.elevation = 2;
		stick7->primary = true;
		stick7->x = 37;
		stick7->y = -45;
		stick7->otherhalf = stick6;
		stickmap[stick7->posKey()] = *stick7.get();
	}
}