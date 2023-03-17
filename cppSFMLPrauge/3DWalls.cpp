#include "mimosdono/3DWalls.h"
#include "mimosdono/Game.h"
#include <memory>
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
			for (std::shared_ptr<walls::Stick>& otherhalf : sop->otherhalves)
			{
				//stickBuffer.push_back(*s.sop);
				float differencey1 = (((s.floorY) - (play.y + 190)) * (s.sop->top.elevation * s.sop->top.elevation)) / 150;
				float differencey2 = (((s.floorY) - (play.y + 190)) * (otherhalf->top.elevation * otherhalf->top.elevation)) / 150;
				float differenceX = (((s.floorX) - (int)play.x) * s.sop->top.elevation);
				float differenceX2 = (((otherhalf->x) - (int)play.x) * otherhalf->top.elevation);
				for (float l = 0; l <= 1; l += .01)
				{
					int yHere = (int)std::lerp(s.sop->y, otherhalf->y, l);
					int xHere = (int)std::lerp(s.floorX, otherhalf->x, l);
					int wallHeightHere = 4+(yHere - (int)std::lerp(s.sop->y + differencey1, otherhalf->y + differencey2, l));
					float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 500;
					float yDifferenceHere = std::lerp(differencey1, differencey2, l) / 100;
					for (int z = 0; z < wallHeightHere; ++z)
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
							brickbetween = -20;
						}
						ob.col = (sf::Color(35 + (z * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting, 35 + (z * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting, 35 + (z * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting));
						ob.obx = xHere;
						ob.oby = yHere ;
						ob.elevation = z;
						if (opixmap.find(keySpot2) == opixmap.end())
						{
							opixmap[keySpot2] = ob;
							if (std::abs(xDifferenceHere) >= .7)
							{
								if (opixmap.find(keySpot22) == opixmap.end())
								{
									opixmap[keySpot22] = ob;
									opixmap[keySpot23] = ob;
								}
								else
								{
									if (opixmap.at(keySpot22).oby < ob.oby)
									{
										opixmap[keySpot22] = ob;
										opixmap[keySpot23] = ob;
									}
								}
							}
						}
						else
						{
							if (opixmap.at(keySpot2).oby < ob.oby)
							{
								opixmap[keySpot2] = ob;
								opixmap[keySpot23] = ob;
							}
						}
					}
				}
			}
		}
		if (buildstickmap.find(keySpot) != buildstickmap.end())
		{
			walls::Stick* sop = &buildstickmap.at(keySpot);
			std::shared_ptr<walls::Stick>& otherhalf = sop->otherhalves[0];

					float differencey1 = (((floorY)-(play.y + 190)) * (sop->top.elevation * sop->top.elevation)) / 150;
				float differencey2 = (((floorY)-(play.y + 190)) * (otherhalf->top.elevation * otherhalf->top.elevation)) / 150;
				float differenceX = (((floorX)-(int)play.x) * sop->top.elevation);
				float differenceX2 = (((otherhalf->x) - (int)play.x) * otherhalf->top.elevation);
				for (float l = 0; l <= 1; l += .01)
				{
					int yHere = (int)std::lerp(sop->y, otherhalf->y, l);
					int xHere = (int)std::lerp(floorX, otherhalf->x, l);
					int wallHeightHere = 4+(yHere - (int)std::lerp(sop->y + differencey1, otherhalf->y + differencey2, l));
					float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 500;
					for (int z = 0; z < wallHeightHere; z++)
					{
						std::string keySpot2 = "" + std::to_string((int)((float)xHere + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
						std::string keySpot22 = "" + std::to_string((int)((float)xHere + 1 + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z);
						objs::ObjectBrick ob;
						ob.col = (sf::Color(100 + (std::abs(sop->y - otherhalf->y) * 4), 140 + (std::abs(sop->y - otherhalf->y) * 4), 100 + (std::abs(sop->y - otherhalf->y) * 4)));
						ob.obx = xHere;
						ob.oby = yHere ;
						ob.elevation = z;
						if (opixmap.find(keySpot2) == opixmap.end())
						{
							opixmap[keySpot2] = ob;
							if (std::abs(xDifferenceHere) >= 2)
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
							if (opixmap.at(keySpot2).oby  < ob.oby)
							{
								opixmap[keySpot2] = ob;
							}
						}
					}
				}

	
			if (std::abs(buildstickmap.at(keySpot).x - buildstickmap.at(keySpot).otherhalves[0]->x) + (std::abs(buildstickmap.at(keySpot).y - buildstickmap.at(keySpot).otherhalves[0]->y)) > 50)
			{
				isBuildingWalls = false;
			}
		}
	}
}