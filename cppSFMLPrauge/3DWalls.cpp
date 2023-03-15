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

namespace jl
{
	void Game::drawSingleWallPixel(int i, int j, bool onOrOff, std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::unordered_map<std::string, walls::Stick>& buildstickmap)
	{
		int floorX = std::floor(i);
		int floorY = std::floor(j);

		std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
		int lastY = camY + 170;
		if (stickmap.find(keySpot) != stickmap.end())
		{
			walls::Stick* sop = &stickmap.at(keySpot);
			sopAndCoord s;
			s.floorX = floorX;
			s.floorY = floorY;
			s.sop = sop;
			lastY = floorY;

			//stickBuffer.push_back(*s.sop);
			float differencey1 = (((s.floorY) - (play.y + 190)) * (s.sop->top.elevation * s.sop->top.elevation)) / 150;
			float differencey2 = (((s.floorY) - (play.y + 190)) * (s.sop->otherhalf->top.elevation * s.sop->otherhalf->top.elevation)) / 150;
			float differenceX = (((s.floorX) - (int)play.x) * s.sop->top.elevation);
			float differenceX2 = (((s.sop->otherhalf->x) - (int)play.x) * s.sop->otherhalf->top.elevation);
			for (float l = 0; l <= 1; l += .005)
			{
				int yHere = (int)std::lerp(s.sop->y, s.sop->otherhalf->y, l);
				int xHere = (int)std::lerp(s.floorX, s.sop->otherhalf->x, l);
				int wallHeightHere = (yHere - (int)std::lerp(s.sop->y + differencey1, s.sop->otherhalf->y + differencey2, l)) * 2;
				float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 150;
				float yDifferenceHere = std::lerp(differencey1, differencey2, l);
				for (int z = 0; z < wallHeightHere; z++)
				{

					std::string keySpot2 = "" + std::to_string((int)((float)xHere + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
					std::string keySpot22 = "" + std::to_string((int)((float)xHere + 1 + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
					std::string keySpot23 = "" + std::to_string((int)((float)xHere - 1 + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
					objs::ObjectBrick ob;
					int brickbetween = 0;
					int brickinterval = 4;
					int bricklighting = (z % brickinterval) * 10;
					if (brickinterval == 0)
					{
						brickinterval = 1;
					}

					bool isBetween = false;
					if (z % brickinterval != 0)
					{
						if (onOrOff)
						{
							if (xHere % (brickinterval * 2) == 0)
							{
								isBetween == true;
							}
						}
						else
						{
							if ((xHere + brickinterval) % (brickinterval * 2) == 0)
							{
								isBetween = true;
							}
						}

					}

					if (z % brickinterval == 0 || isBetween)
					{
						if (z % brickinterval == 0)
						{
							onOrOff = !onOrOff;
						}

						brickbetween = -50;
					}
					ob.col = (sf::Color(50 + (z * 4) + (std::abs(s.sop->y - s.sop->otherhalf->y) * 2) + brickbetween + bricklighting, 50 + (z * 4) + (std::abs(s.sop->y - s.sop->otherhalf->y) * 2) + brickbetween + bricklighting, 50 + (z * 4) + (std::abs(s.sop->y - s.sop->otherhalf->y) * 2) + brickbetween + bricklighting));
					ob.obx = xHere;
					ob.oby = yHere;
					ob.elevation = z;
					if (opixmap.find(keySpot2) == opixmap.end())
					{
						opixmap[keySpot2] = ob;
						if (std::abs(xDifferenceHere) > 2)
						{
							if (opixmap.find(keySpot22) == opixmap.end())
							{
								opixmap[keySpot22] = ob;
							}
							else
							{
								if (opixmap.at(keySpot22).oby < ob.oby)
								{
									opixmap[keySpot22] = ob;
								}
							}
						}
					}
					else
					{
						if (opixmap.at(keySpot2).oby < ob.oby)
						{
							opixmap[keySpot2] = ob;

						}
					}

				}

			}

		}
		if (buildstickmap.find(keySpot) != buildstickmap.end())
		{
			walls::Stick* sop = &buildstickmap.at(keySpot);
			float differencey1 = (((floorY)-(play.y + 190)) * (sop->top.elevation * sop->top.elevation)) / 150;
			float differencey2 = (((floorY)-(play.y + 190)) * (sop->otherhalf->top.elevation * sop->otherhalf->top.elevation)) / 150;
			float differenceX = (((floorX)-(int)play.x) * sop->top.elevation);
			float differenceX2 = (((sop->otherhalf->x) - (int)play.x) * sop->otherhalf->top.elevation);
			for (float l = 0; l <= 1; l += .01)
			{
				int yHere = (int)std::lerp(sop->y, sop->otherhalf->y, l);
				int xHere = (int)std::lerp(floorX, sop->otherhalf->x, l);
				int wallHeightHere = (yHere - (int)std::lerp(sop->y + differencey1, sop->otherhalf->y + differencey2, l)) * 2;
				float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 150;
				for (int z = 0; z < wallHeightHere; z++)
				{

					std::string keySpot2 = "" + std::to_string((int)((float)xHere + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
					std::string keySpot22 = "" + std::to_string((int)((float)xHere + 1 + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
					objs::ObjectBrick ob;
					ob.col = (sf::Color(100 + (std::abs(sop->y - sop->otherhalf->y) * 4), 140 + (std::abs(sop->y - sop->otherhalf->y) * 4), 100 + (std::abs(sop->y - sop->otherhalf->y) * 4)));
					ob.obx = xHere;
					ob.oby = yHere;
					ob.elevation = z;
					if (opixmap.find(keySpot2) == opixmap.end())
					{
						opixmap[keySpot2] = ob;
						opixmap[keySpot22] = ob;
					}
					else
					{
						if (opixmap.at(keySpot2).oby < ob.oby)
						{
							opixmap[keySpot2] = ob;
							opixmap[keySpot22] = ob;
						}
					}
				}

			}
			if (std::abs(buildstickmap.at(keySpot).x - buildstickmap.at(keySpot).otherhalf->x) + (std::abs(buildstickmap.at(keySpot).y - buildstickmap.at(keySpot).otherhalf->y)) < 50)
			{
				window.draw(conv);
			}
			else
			{
				isBuildingWalls = false;
			}
		}
	}
}