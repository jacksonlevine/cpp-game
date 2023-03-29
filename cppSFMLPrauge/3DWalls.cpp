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

	WallPixel::WallPixel(int y, sf::Color col, std::optional<std::weak_ptr<WallPixel>> behind)
	{
		wallY = y;
		myColor = col;
		pixelBehindMe = behind;
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
			if(stickmap.at(keySpot).mapped == false)
			{ 
			walls::Stick* sop = &stickmap.at(keySpot);
			sop->mapped = true;
			sopAndCoord s;
			s.floorX = floorX;
			s.floorY = floorY;
			s.sop = sop;
			lastY = floorY;
			int offsetForElevation = 0;
			if (worldmap.find(keySpot) != worldmap.end())
			{
				offsetForElevation = (int)worldmap.at(keySpot).elevation;
			}
			for (std::shared_ptr<walls::Stick>& otherhalf : sop->otherhalves)
			{
				//stickBuffer.push_back(*s.sop);
				float differencey1 = -10 - elevationBuilding * 16;
				float differencey2 = -10 - elevationBuilding * 16;
				float differenceX = 0;
				float differenceX2 = 0;
				for (float l = 0; l <= 1; l += .01)
				{
					int yHere = (int)std::lerp(s.sop->y, otherhalf->y, l);
					int xHere = (int)std::lerp(s.floorX, otherhalf->x, l);
					int wallHeightHere = 4+(yHere - (int)std::lerp(s.sop->y + differencey1, otherhalf->y + differencey2, l));
					float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 500;
					float yDifferenceHere = std::lerp(differencey1, differencey2, l) / 100;
					for (int z = 0; z < wallHeightHere; ++z)
					{
						std::string keySpot2 = "" + std::to_string((int)((float)xHere + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z - offsetForElevation);


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
						sf::Color col = (sf::Color(35 + (std::min(z, 10) * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting, 35 + (std::min(z, 10) * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting, 35 + (std::min(z, 10) * 4) + (std::abs(s.sop->y - otherhalf->y) * 2) + brickbetween + bricklighting));

						if (wallPixels.find(keySpot2) == wallPixels.end())
						{
							std::shared_ptr<walls::WallPixel> me(new walls::WallPixel(yHere, col, std::nullopt));
							wallPixels[keySpot2] = me;
							sop->myPixels.push_back(me);
						}
						else
						{
							if (wallPixels.at(keySpot2)->wallY < yHere)
							{
								std::weak_ptr other = wallPixels.at(keySpot2);
								std::shared_ptr<walls::WallPixel> me(new walls::WallPixel(yHere, col, other));
								sop->myPixels.push_back(me);
								wallPixels[keySpot2] = me;
							}
							else
							{
								std::shared_ptr<walls::WallPixel> me(new walls::WallPixel(yHere, col, std::nullopt));
								sop->myPixels.push_back(me);
								std::weak_ptr meWeak = me;
								wallPixels.at(keySpot2)->pixelBehindMe = meWeak; // Will need to be changed to sequentially insert itself at the back instead of replacing behind-pixels FUCK.
							}
						}
					}
				}
			}

			}

		}
		// KEEP THIS DOWN HERE THE SAME
		if (buildstickmap.find(keySpot) != buildstickmap.end())
		{
			int offsetForElevation = 0;
			if (worldmap.find(keySpot) != worldmap.end())
			{
				offsetForElevation = (int)worldmap.at(keySpot).elevation;
			}
			walls::Stick* sop = &buildstickmap.at(keySpot);
			std::shared_ptr<walls::Stick>& otherhalf = sop->otherhalves[0];

			float differencey1 = -10-elevationBuilding*16;
			float differencey2 = -10-elevationBuilding*16;
			float differenceX = 0;
			float differenceX2 = 0;
				for (float l = 0; l <= 1; l += .005)
				{
					int yHere = (int)std::lerp(sop->y, otherhalf->y, l);
					int xHere = (int)std::lerp(floorX, otherhalf->x, l);
					int wallHeightHere = 4+(yHere - (int)std::lerp(sop->y + differencey1, otherhalf->y + differencey2, l));
					float xDifferenceHere = std::lerp(differenceX, differenceX2, l) / 500;
					for (int z = 0; z < wallHeightHere; z++)
					{
						std::string keySpot2 = "" + std::to_string((int)((float)xHere + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z - offsetForElevation);
						std::string keySpot22 = "" + std::to_string((int)((float)xHere + 1 + (xDifferenceHere * (float)z))) + ',' + std::to_string(yHere - z - offsetForElevation);
						objs::ObjectBrick ob;
						ob.col = (sf::Color(100 + (std::abs(sop->y - otherhalf->y) * 4), 140 + (std::abs(sop->y - otherhalf->y) * 4), 100 + (std::abs(sop->y - otherhalf->y) * 4)));
						ob.obx = xHere;
						ob.oby = yHere ;
						ob.elevation = z;
						if (opixmap.find(keySpot2) == opixmap.end())
						{
							opixmap[keySpot2] = ob;
						}
						else
						{
							if (opixmap.at(keySpot2).oby  < ob.oby || opixmap.at(keySpot2).isReflection)
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