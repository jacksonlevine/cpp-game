#include "mimosdono/JacksObjects.h"
#include "mimosdono/Game.h"

namespace objs
{
	int FixedObject::reflectionOffset = 20;
	FixedObject::FixedObject()
	{
		width = 0;
		height = 0;
		type = 0;
		x = 0;
		y = 0;
		strength = 10;
	};
	FixedObject::FixedObject(std::string thi, int wi, int he, int ty)
	{
		x = 0;
		y = 0;
		strength = 10;
		thing = thi;
		width = wi;
		height = he;
		type = ty;
	}
	void FixedObject::clickEvent()
	{
		strength -= 1;
	}
}

namespace jl
{
	void Game::processMouseClickedOnObjectPixel(std::unordered_map<std::string, objs::ObjectBrick>& opixmap)
	{
		if (mouseClicked == true)
		{
			setClickPos();
			if (clickTimer <= 0.1)
			{
				clickTimer = clickInterval;
				std::string keySpot = "" + std::to_string(((int)std::round(click.x) / ts) + (int)camX) + ',' + std::to_string(((int)std::round(click.y) / ts) + (int)camY);
				if (opixmap.find(keySpot) != opixmap.end())
				{
					opixmap.at(keySpot).point->clickEvent();
					for (int n = 0; n < 1; n++)
					{
						spawnParticleFromObjectPixel(opixmap, keySpot);
					}
				}
			}
			else
			{
				clickTimer -= 2;
			}
		}
	}
	void Game::spawnParticleFromObjectPixel(std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::string& keySpot)
	{
		objs::Particle pa;
		pa.x = (((int)std::round(opixmap.at(keySpot).obx - ((opixmap.at(keySpot).point->width / 2) * ((float)std::rand() / RAND_MAX)) + opixmap.at(keySpot).point->width / 4))) - 3;
		pa.y =  ((int)std::round(opixmap.at(keySpot).oby - ((opixmap.at(keySpot).point->height / 1.5) * ((float)std::rand() / RAND_MAX))));
		sf::Color c = opixmap.at(keySpot).col;
		c.r += 50;
		c.g += 50;
		c.b += 50;
		pa.col = c;
		parts.push_back(pa);
	}
	void Game::breakFixedObjectAndDropItems(std::string& keySpot)
	{
		int dropCount = (int)(((float)std::rand() / RAND_MAX) * 10);
		for (int n = 0; n < dropCount; n++)
		{
			float xOff = (int)(((float)std::rand() / RAND_MAX) * -7 + 3.5) - 2;
			float yOff = (int)(((float)std::rand() / RAND_MAX) * -5 + 2.5) - objs::FixedObject::reflectionOffset;
			objs::DroppedItem d(fomap.at(keySpot).x + xOff, fomap.at(keySpot).y + yOff, (int)drops.size());
			if (fomap.at(keySpot).type == 0)
			{
				d.thing = "tttttt";
				d.height = 2;
				d.width = 3;
				d.name = "wood";
				d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
			}
			else if (fomap.at(keySpot).type == 1)
			{
				d.thing = "00a0aasaasna0nna";
				d.height = 4;
				d.width = 4;
				d.name = "stone";
				d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
			}
			else
			{
				d.thing = "0a0ata0a0";
				d.width = 3;
				d.height = 3;
				d.name = "no texture";
				d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
			}
			drops.push_back(d);
		}
		for (int n = 0; n < 25; n++)
		{
			objs::Particle pa;
			pa.x = (((int)std::round(fomap.at(keySpot).x - ((fomap.at(keySpot).width / 2) * ((float)std::rand() / RAND_MAX)) + fomap.at(keySpot).width / 4))) - 2;
			pa.y = ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height / 1.5) * ((float)std::rand() / RAND_MAX)))) - objs::FixedObject::reflectionOffset;
			sf::Color c = opixref[fomap.at(keySpot).thing[((fomap.at(keySpot).height - 1) * fomap.at(keySpot).width) + (int)(fomap.at(keySpot).width / 2)]];
			c.r += 50;
			c.g += 50;
			c.b += 50;
			pa.col = c;
			parts.push_back(pa);
		}
		fomap.erase(keySpot);
	}
	void Game::addFixedObjectPixelsToBuffer(std::unordered_map<std::string, objs::ObjectBrick>& opixmap, int floorY, int floorX, perlin& p)
	{
		std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
		if (fomap.find(keySpot) != fomap.end())
		{
			if (fomap.at(keySpot).strength < 0)
			{
				breakFixedObjectAndDropItems(keySpot);
			}
			else
			{
				objs::FixedObject* fop = &fomap.at(keySpot);
				int wi = fop->width;
				int he = fop->height;
				for (int f = 0; f < he; f++)
				{
					for (int o = 0; o < wi; o++)
					{
						char t = fop->thing[(f * wi) + o];
						if (t != '0')
						{
							objs::ObjectBrick ob(opixref[t], fop->x, fop->y);
							ob.elevation = he - f;
							if (worldmap.find(keySpot) != worldmap.end())
							{
								ob.elevation += worldmap.at(keySpot).elevation;
							}
							int difference = (((floorY)-(int)(play.y + 150)) * ob.elevation);
							int differenceX = (((floorX)-(int)play.x) * ob.elevation);
							int ksx = floorX + (int)((((o * 1) - 15) + (differenceX >> 8)));
							int ksy = -objs::FixedObject::reflectionOffset + floorY + (int)(((f << 2) + (difference >> 4)) >> 3) / 2;

							std::string thisKeySpot = "" + std::to_string(ksx) + ',' + std::to_string(ksy);
							ob.oby = fop->y - objs::FixedObject::reflectionOffset;
							ob.point = fop;
							if (opixmap.find(thisKeySpot) == opixmap.end())
							{
								if (ob.col == opixref['l'])
								{
									int n22 = std::floor(p.noise((o + floorX) * 0.1, (o + floorX) * 0.2, 11.01 + ((int)perlinZEffect2 >> 8)) * 10);
									int n32 = std::floor(p.noise((f + floorY) * 0.1, (f + floorY) * 0.4, 11.01 + ((int)perlinZEffect2 >> 8)) * 4);
									int n2Clamped = (std::min(std::max(n22 - n32 - 4, -8), 8));
									thisKeySpot = "" + std::to_string((n2Clamped >> 2) + ksx) + ',' + std::to_string(ksy);
									if ((float)std::rand() / RAND_MAX > 0.9999)
									{
										objs::Particle pa;
										pa.x = (((int)std::round(fomap.at(keySpot).x - ((fomap.at(keySpot).width / 2) * ((float)std::rand() / RAND_MAX)) + fomap.at(keySpot).width / 4)));
										pa.y = -7 + ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height >> 1) * ((float)std::rand() / RAND_MAX))));
										sf::Color c = opixref['l'];
										pa.speedY = std::max(pa.speedY, 0.1f);
										pa.speedX = ((float)std::rand() / RAND_MAX) - 0.5f;
										pa.col = c;
										parts.push_back(pa);
									}
								}
								opixmap[thisKeySpot] = ob;
							}
							else
							{
								if (opixmap.at(thisKeySpot).oby < fop->y)
								{
									opixmap[thisKeySpot] = ob;
								}
							}
						}
					}
				}
				for (int f = 0; f < he; f++)
				{
					for (int o = 0; o < wi; o++)
					{
						char t = fop->thing[objs::clamp((f * wi) + o, 0, (wi * he) - 2)];
						if (t != '0')
						{
							objs::ObjectBrick ob(opixref[t], fop->x, fop->y);
							ob.elevation = he - f;
							if (worldmap.find(keySpot) != worldmap.end())
							{
								ob.elevation += worldmap.at(keySpot).elevation;
							}
							int difference = (((floorY)-(int)(play.y + 150)) * ob.elevation);
							int differenceX = (((floorX)-(int)play.x) * ob.elevation);
							int n22 = std::floor(p.noise((o + floorX) * 0.1, (o + floorX) * 0.2, 11.01 + ((int)perlinZEffect2 >> 10)) * 10);
							int n32 = std::floor(p.noise((f + floorY) * 0.1, (f + floorY) * 0.4, 11.01 + ((int)perlinZEffect2 >> 5)) * 4);
							int n2Clamped = (std::min(std::max(n22 - n32 - 4, -8), 8));
							int off = (fop->type == 0) ? 18 : 0;
							int ksx = floorX + (int)((((o * 1) - 15) + (differenceX >> 8)));
							int ksy = -objs::FixedObject::reflectionOffset + (n2Clamped >> 1) + floorY + 19 - (he + 3 - off) - (int)((((f >> 4) + (difference >> 4)) >> 5) >> 2) + 3;
							std::string thisKeySpot = "" + std::to_string(ksx) + ',' + std::to_string(ksy);
							ob.col.b = std::min(std::max((int)ob.col.b, 25), 150);
							ob.col.r = std::min(std::max((int)ob.col.r, 25), 150);
							ob.col.g = std::min(std::max((int)ob.col.g, 25), 150);
							ob.col.a = 120;
							ob.point = fop;
							ob.oby = fop->y - objs::FixedObject::reflectionOffset;
							if (opixmap.find(thisKeySpot) == opixmap.end())
							{
								if (worldmap.find(thisKeySpot) != worldmap.end())
								{
									if (worldmap.at(thisKeySpot).isWater == true)
									{
										opixmap[thisKeySpot] = ob;
									}
								}
							}
							else
							{
								if (opixmap.at(thisKeySpot).oby < fop->y)
								{
									if (worldmap.at(thisKeySpot).isWater == true)
									{
										opixmap[thisKeySpot] = ob;
									}
								}
							}
						}
					}
				}
				perlinZEffect2 += .2;
			}
		}
	}
}