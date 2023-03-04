#pragma once
#include "mimosdono/JacksObjects.h"
#include "mimosdono/perlin.h"
namespace world
{
	class World
	{
	public:
		static std::unordered_map<std::string, objs::ColorBrick> generateWorld(perlin p, int ws, std::unordered_map<std::string, objs::FixedObject> &fomap)
		{
			std::unordered_map<std::string, objs::ColorBrick> wmap;
			sf::Color col;
			objs::ColorBrick brick(col, 0);
			std::srand(std::time(0));
			float offset = ((float)std::rand() / RAND_MAX) * 10000000;
			for (int j = -ws; j < ws; j++)
			{
				for (int i = -ws; i < ws; i++)
				{
					double n = p.noise(i * 0.01, j * 0.01, 11.01 + offset) * 10;
					double n2 = p.noise(i * 0.05, j * 0.05, 11.01 + offset) * 4;
					double n3 = p.noise(i * 0.01, j * 0.01, 11.01 + offset) * 4;
					double n4 = p.noise(i * 0.9, j * 0.9, 11.01 + offset) / 2;
					double n5 = p.noise(i * 0.009, j * 0.009, 7.01 + offset) * 15;
					double ln = (p.noise(i * 0.02, j * 0.02, 93.0122 + offset) * 10) + (n4 * 2);
					double nClamped = std::min(std::min(n5 + std::max(n + std::max(n3 - 2 - n2, 0.0), 0.0), 10.0), 4.5) + std::max(n4, 0.0);
					int floorX = std::floor(i);
					int floorY = std::floor(j);
					std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
					int sandLvl = 2.8;
					float waterLvl = 0.6;
					if (nClamped > waterLvl && nClamped < sandLvl)
					{
						brick.isWater = false;
						float red = (70 + 320 * (nClamped / 10));
						float green = (70 + 310 * (nClamped / 10));
						float blue = (237 * (nClamped / 6));
						float a = (255);
						float elev = nClamped;
						insertIntoWorld(floorX, floorY, red, green, blue, a, elev, &wmap, brick);
					}
					else if (nClamped > sandLvl)
					{
						if (ln < 2)
						{
							brick.isWater = false;
							float red = std::min(25 + 5 * (nClamped * 3), 204.5);
							float green = std::min(25 + 10 * (nClamped * 3), 204.5);
							float blue = (2 * (nClamped * 3));
							float a = (255);
							float elev = nClamped;
							insertIntoWorld(floorX, floorY, red, green, blue, a, elev, &wmap, brick);
							if (std::rand() > 32750)
							{
								objs::FixedObject rock;
								rock.x = floorX;
								rock.y = floorY;
								rock.width = 23;
								rock.height = 15;
								rock.thing = objs::Rock::makeRock();
								rock.type = 1;
								std::string keySpot2 = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
								fomap[keySpot2] = rock;
							}
						}
						else 
						{
							brick.isWater = false;
							float red = (25 + 17 * nClamped + (n4 * 100));
							float green = (25 + 10 * nClamped + (n4 * 100));
							float blue = (std::min(9 * nClamped + (n4 * 30), 50.0));
							float a = (255);
							float elev = nClamped;
							if (std::rand() > 32500)
							{
								objs::FixedObject tree;
								tree.x = floorX;
								tree.y = floorY;
								tree.width = 26;
								tree.height = 25;
								tree.thing = objs::Tree::makeTree();
								tree.type = 0;
								std::string keySpot3 = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
								fomap[keySpot3] = tree;
							}
							insertIntoWorld(floorX, floorY, red, green, blue, a, elev, &wmap, brick);
						}
					}
					else
					{
						if (std::rand() > 32750)
						{
							objs::FixedObject tree;
							tree.x = floorX;
							tree.y = floorY;
							tree.width = 26;
							tree.height = 25;
							tree.thing = objs::Tree::makeTree();
							tree.type = 0;
							std::string keySpot3 = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
							fomap[keySpot3] = tree;
						}
						float red = (0);
						float green = (0);
						float blue = (0);
						float a = (0);
						float elev = (nClamped / 3) + 1;
						brick.isWater = true;
						insertIntoWorld(floorX, floorY, red, green, blue, a, elev, &wmap, brick);
					}
				}
			}
			return wmap;
		}
		static void insertIntoWorld(int x, int y, float red, float green, float blue, float a, float elevation, std::unordered_map<std::string, objs::ColorBrick>* wmap, objs::ColorBrick brick)
		{
			brick.col.r = red;
			brick.col.g = green;
			brick.col.b = blue;
			brick.col.a = a;
			brick.elevation = elevation;
			std::string keySpot = "" + std::to_string(x) + ',' + std::to_string(y);
			wmap->insert_or_assign(keySpot, brick);
		}
		static std::unordered_map<char, sf::Color> getObjectPixReferences()
		{
			std::unordered_map<char, sf::Color> opixref;
			sf::Color ocols;
			ocols.r = 52;
			ocols.g = 26;
			ocols.b = 12;
			ocols.a = 255;
			opixref['t'] = ocols;
			ocols.r = 40;
			ocols.g = 200;
			ocols.b = 35;
			ocols.a = 255;
			opixref['l'] = ocols;
			ocols.r = 36;
			ocols.g = 150;
			ocols.b = 26;
			ocols.a = 255;
			opixref['b'] = ocols;
			ocols.r = 100;
			ocols.g = 100;
			ocols.b = 100;
			ocols.a = 255;
			opixref['n'] = ocols;
			ocols.r = 150;
			ocols.g = 150;
			ocols.b = 150;
			ocols.a = 255;
			opixref['s'] = ocols;
			ocols.r = 50;
			ocols.g = 50;
			ocols.b = 50;
			ocols.a = 255;
			opixref['a'] = ocols;
			ocols.r = 132;
			ocols.g = 79;
			ocols.b = 10;
			ocols.a = 255;
			opixref['c'] = ocols;
			ocols.r = 223;
			ocols.g = 184;
			ocols.b = 104;
			ocols.a = 255;
			opixref['h'] = ocols;
			return opixref;
		}
	};
}