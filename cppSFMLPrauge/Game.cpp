#pragma once
#include "mimosdono/World.h"
#include "mimosdono/Game.h"
#include <iostream>
namespace jl
{
	Game::Game()
	{
		gameWidth = 1280;
		gameHeight = 720;
		window.create(sf::VideoMode(gameWidth, gameHeight), "MimosDono Dev 12.2.0");
		camX = 0;
		camY = 0;
		ws = 1000;
		ts = 14;
		sf::Vector2f click;
		mouseClicked = false;
		clickTimer = 0;
		clickInterval = 10;
		selectedInv = 0;
		minimapWidth = 20;
		invTiles = 5;
		invTileSpacing = (int)((float)(minimapWidth * ts) / invTiles) + (int)((float)ts / invTiles);
		minimapX = (gameWidth/ts)-(minimapWidth);
		minimapY = (gameHeight/ts)-(minimapWidth)-(invTileSpacing/ts);
		invY = (minimapY * ts) + (minimapWidth * ts) + 10;
		test = false;
		clickOnMinimap = false;
		clickPositionSet = false;
		perlinZEffect = 0;
		perlinZEffect2 = 0;
		testNum = -20;
		oboverscan = 20;
		typeID =
		{
			{
				"stone", 0
			},
			{
				"wood", 1
			},
			{
				"no texture", 2
			}
		};
		worldmap = world::World::generateWorld(p, ws, fomap);
		opixref = world::World::getObjectPixReferences();
		click = sf::Vector2f(-1, -1);
		play = objs::Player("Player1", (window.getSize().x / ts) / 2, (window.getSize().y / ts) / 2);
		invRect = sf::RectangleShape(sf::Vector2f((int)invTileSpacing - 7, (int)invTileSpacing - 7));
		invItemRect = sf::RectangleShape(sf::Vector2f(7, 7));
		invRect.setFillColor(sf::Color(0, 0, 0));
		invItemRect.setFillColor(sf::Color(255, 255, 255));
		rect = sf::RectangleShape(sf::Vector2f(ts, ts));
		size = window.getSize();
		width = size.x / ts;
		height = size.y / ts;
		pmap[play.posKey()] = &play;
		if (!font.loadFromFile("Akilvan.ttf"))
		{
			std::cout << "Failed to load font";
		}
		text.setFont(font);
		text.setCharacterSize(15);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Regular);
	};
	void Game::pollEvents(sf::Event e) {
		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {

				setClickPos();
				bool clickPosOnMinimap = (click.x / ts > minimapX && click.y / ts > minimapY && click.x / ts < minimapX + minimapWidth && click.y / ts < minimapY + minimapWidth);
				if (clickPosOnMinimap)
				{
					clickOnMinimap = true;
				}
				else
				{
					mouseClicked = true;
					clickTimer = 0;
				}
			}
			if (e.mouseButton.button == sf::Mouse::Right)
			{
				setClickPos();
				placeCurrentItem();
			}
		}
		if (e.type == sf::Event::MouseButtonReleased)
		{
			clickOnMinimap = false;
			clickPositionSet = false;
			mouseClicked = false;
		}
		if (e.type == sf::Event::Closed)
		{
			window.close();
		}
		if (e.type == sf::Event::MouseWheelScrolled)
		{
			int s = (int)e.mouseWheelScroll.delta;
			if (selectedInv + s >= 0 && selectedInv + s <= invTiles - 1)
			{
				selectedInv += s;
			}
		}
	}

	void Game::placeCurrentItem()
	{
		if (play.inv.inv[selectedInv].id == 0)
		{
			objs::FixedObject rock;
			rock.x = (int)(click.x / ts + camX) + 5;
			rock.y = (int)(click.y / ts + camY) + 18;
			rock.width = 23;
			rock.height = 15;
			rock.thing = objs::Rock::makeRock();
			rock.type = 1;
			std::string keySpot2 = "" + std::to_string(rock.x) + ',' + std::to_string(rock.y);
			fomap[keySpot2] = rock;
			if (play.inv.inv[selectedInv].count > 1)
			{
				play.inv.inv[selectedInv].count -= 1;
			}
			else
			{
				play.inv.inv[selectedInv].id = -1;
				play.inv.inv[selectedInv].count = -1;
			}
		}
	}

	void Game::draw()
	{
		window.clear(sf::Color::Black);
		render(p);
		renderMinimap(minimapWidth, minimapX, minimapY, &play);
		moveGUIElements();
		renderUI();
		handleEvents(&play);
		window.display();
	}

	void Game::moveGUIElements()
	{
		if (clickOnMinimap == true)
		{
			float xPrev = click.x;
			float yPrev = click.y;
			setClickPos();
			float xNow = click.x;
			float yNow = click.y;
			float xdiff = xNow - xPrev;
			float ydiff = yNow - yPrev;
			minimapX += xdiff / ts;
			minimapY += ydiff / ts;
		}
	}

	void Game::setClickPos()
	{
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		float xRatio = (float)size.x / (float)window.getViewport(window.getView()).width;
		float yRatio = (float)size.y / (float)window.getViewport(window.getView()).height;
		click.x = (int)std::round(pos.x * xRatio);
		click.y = (int)std::round(pos.y * yRatio);
	}

	bool Game::isMouseOver(sf::RectangleShape* recto)
	{
		setClickPos();
		sf::Vector2f rectPos = recto->getPosition();
		sf::Vector2f rectSize = recto->getSize();
		if (click.x >= rectPos.x && click.x <= rectPos.x + rectSize.x && click.y >= rectPos.y && click.y <= rectPos.y + rectSize.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Game::renderUI()
	{
		text.setString("MimosDono v12.2.0dev");
		text.setPosition(sf::Vector2f(0, 0));
		window.draw(text);
		for (int i = 0; i < invTiles; i++)
		{
			int invX = (minimapX * ts) + (i * invTileSpacing);
			bool thisSlotSelected = (selectedInv == i);
			bool slotIsEmpty = (play.inv.inv[i].id == -1);
			invRect.setPosition(sf::Vector2f(invX, invY));
			invRect.setFillColor((isMouseOver(&invRect) || thisSlotSelected) ? sf::Color(50, 50, 50) : sf::Color(0, 0, 0));
			if (thisSlotSelected)
			{
				invRect.setOutlineColor(sf::Color(255, 255, 255));
				invRect.setOutlineThickness(2);
			}
			else
			{
				invRect.setOutlineThickness(0);
			}
			window.draw(invRect);
			if (!slotIsEmpty)
			{
				drawInventoryTileContent(i, invX);
			}
		}
	}
	void Game::drawInventoryTileContent(int i, int invX)
	{
		int wi = play.inv.inv[i].thingWidth;
		int he = play.inv.inv[i].thingHeight;
		std::string thing = play.inv.inv[i].thing;
		text.setString((sf::String)std::to_string(play.inv.inv[i].count));
		text.setPosition(sf::Vector2f(invX + ts, invY + ts + ts));
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		for (int h = 0; h < he; h++)
		{
			for (int t = 0; t < wi; t++)
			{
				char s = thing[(h * wi) + t];
				if (thing[s] != '0')
				{
					invItemRect.setFillColor(opixref[s]);
					invItemRect.setPosition(sf::Vector2f((invX + ((1.5 / wi) * ts)) + (t * invItemRect.getSize().x), (invY + ((1.5 / he) * ts)) + (h * invItemRect.getSize().y)));
					window.draw(invItemRect);
					window.draw(text);
				}
			}
		}
	}
	void Game::render(perlin p)
	{
		std::unordered_map<std::string, objs::ObjectBrick> opixmap;
		std::unordered_map<std::string, objs::PlayerPixel> screenumap;
		updateDropsAndAddToScreenBuffer(screenumap);
		for (int j = oboverscan + height + camY + 1; j > -oboverscan + 0 + camY - 1; j--)
		{
			for (int i = -oboverscan + 0 + camX - 1; i < width + camX + 1 + oboverscan; i++)
			{
				int floorX = std::floor(i);
				int floorY = std::floor(j);
				addPlayerPixelsToBuffer(floorX, floorY, screenumap);
				addFixedObjectPixelsToBuffer(opixmap, floorY, floorX, p);
				decidePixelAndDrawIfWithinScreenBounds(floorX, floorY, opixmap, screenumap, p);
			}
		}
		drawAndUpdateParticles();
		processMouseClickedOnObjectPixel(opixmap);
		perlinZEffect++;
	}
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
		pa.y = -15 + ((int)std::round(opixmap.at(keySpot).oby - ((opixmap.at(keySpot).point->height / 1.5) * ((float)std::rand() / RAND_MAX))));
		sf::Color c = opixmap.at(keySpot).col;
		c.r += 50;
		c.g += 50;
		c.b += 50;
		pa.col = c;
		parts.push_back(pa);
	}
	void Game::decidePixelAndDrawIfWithinScreenBounds(int i, int j, std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::unordered_map<std::string, objs::PlayerPixel>& screenumap, perlin& p)
	{
		std::string keySpot = "" + std::to_string(i) + ',' + std::to_string(j);
		if (i > camX - 1 && i < width + camX + 1 && j > 0 + camY - 1 && j < height + camY + 1)
		{
			bool isObjectPix = false;
			if (opixmap.find(keySpot) != opixmap.end())
			{
				rect.setFillColor(opixmap.at(keySpot).col);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				window.draw(rect);
				isObjectPix = true;
			}
			if (screenumap.find(keySpot) != screenumap.end())
			{
				if (opixmap.find(keySpot) == opixmap.end())
				{
					rect.setFillColor(screenumap.at(keySpot).col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					window.draw(rect);
				}
				else
				{
					if (opixmap.at(keySpot).oby < screenumap.at(keySpot).py)
					{
						rect.setFillColor(screenumap.at(keySpot).col);
						rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
						window.draw(rect);
					}
					else
					{
						rect.setFillColor(opixmap.at(keySpot).col);
						rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
						window.draw(rect);
					}
				}
			}
			else if (worldmap.find(keySpot) != worldmap.end() && isObjectPix == false)
			{
				if (worldmap.at(keySpot).col.a > 0)
				{
					rect.setFillColor(worldmap.at(keySpot).col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					window.draw(rect);
				}
				else
				{
					int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + ((int)perlinZEffect >> 8)) * 10);
					int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + ((int)perlinZEffect >> 4)) * 4);
					int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
					float waterLight = std::max(worldmap.at(keySpot).elevation, 0.0f) * 10;
					sf::Color col;
					col.r = (1 * n2Clamped + 1 + (waterLight * 5));
					col.g = (50 + n2Clamped + (waterLight * 5) + (15 * n2Clamped));
					col.b = (75 + (n2Clamped * 2) + (15 * n2Clamped) + (waterLight * 5));
					col.a = 120;
					rect.setFillColor(col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					window.draw(rect);
				}
			}
			else if (isObjectPix == false)
			{
				int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + ((int)perlinZEffect >> 8)) * 10);
				int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + ((int)perlinZEffect >> 4)) * 4);
				int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
				sf::Color col;
				col.r = (15 * n2Clamped + 1);
				col.g = (15 * n2Clamped);
				col.b = (90 + (n2Clamped * 2));
				col.a = 120;
				rect.setFillColor(col);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				window.draw(rect);
			}
		}
	}
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
	void Game::breakFixedObjectAndDropItems(std::string& keySpot)
	{
		int dropCount = (int)(((float)std::rand() / RAND_MAX) * 10);
		for (int n = 0; n < dropCount; n++)
		{
			float xOff = (int)(((float)std::rand() / RAND_MAX) * -7 + 3.5) - 2;
			float yOff = -12 + (int)(((float)std::rand() / RAND_MAX) * -5 + 2.5);
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
			pa.y = -15 + ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height / 1.5) * ((float)std::rand() / RAND_MAX))));
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
							int ksy = floorY - 20 + (int)(((f * 8) + (difference >> 4)) / 10) / 2;

							std::string thisKeySpot = "" + std::to_string(ksx) + ',' + std::to_string(ksy);

							ob.point = fop;
							if (opixmap.find(thisKeySpot) == opixmap.end())
							{
								if (ob.col == opixref['l'])
								{
									int n22 = std::floor(p.noise((o + floorX) * 0.1, (o + floorX) * 0.2, 11.01 + ((int)perlinZEffect2 >> 8)) * 10);
									int n32 = std::floor(p.noise((f + floorY) * 0.1, (f + floorY) * 0.4, 11.01 + ((int)perlinZEffect2 >> 8)) * 4);
									int n2Clamped = (std::min(std::max(n22 - n32 - 4, -8), 8));
									thisKeySpot = "" + std::to_string((n2Clamped / 4) + ksx) + ',' + std::to_string(ksy);
									if ((float)std::rand() / RAND_MAX > 0.9999)
									{
										objs::Particle pa;
										pa.x = (((int)std::round(fomap.at(keySpot).x - ((fomap.at(keySpot).width / 2) * ((float)std::rand() / RAND_MAX)) + fomap.at(keySpot).width / 4)));
										pa.y = -15 + ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height / 1.5) * ((float)std::rand() / RAND_MAX))));
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
							int n22 = std::floor(p.noise((o + floorX) * 0.1, (o + floorX) * 0.2, 11.01 + (perlinZEffect2 / 500)) * 10);
							int n32 = std::floor(p.noise((f + floorY) * 0.1, (f + floorY) * 0.4, 11.01 + (perlinZEffect2 / 300)) * 4);
							int n2Clamped = (std::min(std::max(n22 - n32 - 4, -8), 8));
							int off = (fop->type == 0) ? 18 : 0;
							int ksx = floorX + (int)((((o * 1) - 15) + (differenceX >> 8)));
							int ksy = (n2Clamped / 2) + floorY - (he + 3 - off) - (int)((((f / 8) + (difference >> 4)) / 10) >> 2) + 3;
							std::string thisKeySpot = "" + std::to_string(ksx) + ',' + std::to_string(ksy);
							ob.col.b = std::min(std::max((int)ob.col.b, 25), 150);
							ob.col.r = std::min(std::max((int)ob.col.r, 25), 150);
							ob.col.g = std::min(std::max((int)ob.col.g, 25), 150);
							ob.col.a = 120;
							ob.point = fop;
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
	void Game::renderMinimap(int widt, int x, int y, objs::Player* pla)
	{
		int revScale = 20;
		for (int j = y; j < y + widt; j++)
		{
			for (int i = x; i < x + widt; i++)
			{
				int localX = (int)(pla->x + ((i - x) * revScale) - ((widt * revScale) / 2));
				int localY = (int)(pla->y + ((j - y) * revScale) - ((widt * revScale) / 2));
				std::string keySpot = "" + std::to_string(localX) + ',' + std::to_string(localY);
				if (worldmap.find(keySpot) != worldmap.end())
				{
					if (worldmap.at(keySpot).isWater != true)
					{
						rect.setFillColor(worldmap.at(keySpot).col);
						rect.setPosition(sf::Vector2f(i * ts, j * ts));
						window.draw(rect);
					}
					else
					{
						rect.setFillColor(sf::Color::Blue);
						rect.setPosition(sf::Vector2f(i * ts, j * ts));
						window.draw(rect);
					}
				}
			}
		}
	}
	void Game::handleEvents(objs::Player* pla)
	{
		float movement = 1.2;
		if (window.hasFocus())
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
			{
				testNum += 1;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
			{
				setClickPos();
				objs::Chest ch;
				ch.x = (int)(click.x / ts + camX) + 10;
				ch.y = (int)(click.y / ts + camY) + 18;
				std::string keySpot2 = "" + std::to_string(ch.x) + ',' + std::to_string(ch.y);
				fomap[keySpot2] = ch;

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				camX -= movement;
				pla->move(-movement, 0, &pmap);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				camX += movement;
				pla->move(movement, 0, &pmap);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				camY += movement;
				pla->move(0, movement, &pmap);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				camY -= movement;
				pla->move(0, -movement, &pmap);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				if (pla->jump == false)
				{
					pla->jump = true;
				}
			}
		}
	}
}