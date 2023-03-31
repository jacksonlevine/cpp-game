#pragma once
#include "mimosdono/World.h"
#include "mimosdono/Game.h"
#include "mimosdono/MimosDonoDefaultGUI.h"
#include "mimosdono/3DWalls.h"
#include <iostream>
#include <pgobootrun.h>
/*//ThiTTs isHH becoEEmingDD a EEVVmeIIssLL IISS HHEERREE WOoRhSHIp#((01111101111111111!!!!!!!!!!!!!000*/
namespace jl
{
	gui::GUIObject* currentMousedOver;
	Game::Game()
	{
		mouseSlot = objs::InventorySlot();
		isFullscreen = false;
		buildingStickPrimary = std::shared_ptr<walls::Stick>(new walls::Stick);
		buildingStickSecondary = std::shared_ptr<walls::Stick>(new walls::Stick);
		buildingStickPrimary->otherhalves.push_back(buildingStickSecondary);
		buildingStickSecondary->otherhalves.push_back(buildingStickPrimary);
		mousedOverAGuiItem = false;
		currentgui = "pause";
		isGUIOpen = false;
		versionString = "MimosDono Dev 12.3.1";
		isMinimapExpanded = true;
		guiKeyJustTriggered = false;
		gameWidth = 1280;
		gameHeight = 720;
		sf::ContextSettings c;
		c.antialiasingLevel = 0;
		
		window.create(sf::VideoMode(gameWidth, gameHeight), versionString, sf::Style::Default, c);
		window.setVerticalSyncEnabled(true);
		camX = 0;
		camY = 0;
		ws = 1000;
		ts = 9;
		sf::Vector2f click; 
		mouseClicked = false;
		clickTimer = 0;
		clickInterval = 10;
		selectedInv = 0;
		elevationBuilding = 0;
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
		oboverscan = 22;
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
			},
			{
				"wall builder", 3
			}
		};
		worldmap = world::World::generateWorld(p, ws, fomap);
		opixref = world::World::getObjectPixReferences();
		click = sf::Vector2f(-1, -1);
		play = objs::Player("Player1", (window.getSize().x / ts) / 2, (window.getSize().y / ts) / 2);
		play.us = true;
		invRect = sf::RectangleShape(sf::Vector2f((int)invTileSpacing - 7, (int)invTileSpacing - 7));
		invItemRect = sf::RectangleShape(sf::Vector2f(7, 7));
		invRect.setFillColor(sf::Color(0, 0, 0));
		invItemRect.setFillColor(sf::Color(255, 255, 255));
		rect = sf::RectangleShape(sf::Vector2f(ts*2, ts*2));
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

		conv.setFillColor(sf::Color(100,100,100));
		addTestThingsToInventory();
		gui::GUIController::setViews(gui::MimosDonoDefaultGUI::getViews(this, gameWidth, gameHeight));
	};
	void Game::addTestThingsToInventory()
	{
		play.inv.inv[0].id = 3;
		play.inv.inv[0].count = 1;
		play.inv.inv[0].thing = "aaaaaassnaasnnaannnaannna";
		play.inv.inv[0].thingWidth = 5;
		play.inv.inv[0].thingHeight = 5;
		play.inv.inv[0].name = "wall builder";
	}
	void Game::switchOrToggleGui(std::string newView)
	{
		if (isGUIOpen && currentgui != newView) { currentgui = newView; }
		else { currentgui = newView; isGUIOpen = !isGUIOpen; }
	}

	void Game::pollEvents(sf::Event e) {
		//renderUI();
		if (e.type == sf::Event::KeyPressed) 
		{
			if (e.key.code == sf::Keyboard::E)
			{
				switchOrToggleGui("inventory");

			}
			if (e.key.code == sf::Keyboard::Escape)
			{
				switchOrToggleGui("pause");
			}
			if (!isGUIOpen)
			{
				float movement = 260.2;
				//DEBUG SETTINGS
				if (e.key.code == sf::Keyboard::K)
				{
					testNum += 1;
				}
				if (e.key.code == sf::Keyboard::C)
				{
					setClickPos();
					objs::Chest ch;
					ch.x = (int)(click.x / ts + camX) + 10;
					ch.y = (int)(click.y / ts + camY) + 18;
					std::string keySpot2 = "" + std::to_string(ch.x) + ',' + std::to_string(ch.y);
					fomap[keySpot2] = ch;
				}
				//END DEBUG
				if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::A)
				{
					play.left = true;
				}
				if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::D)
				{
					play.right = true;
				}
				if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S)
				{
					play.down = true;
				}
				if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W)
				{
					play.up = true;
				}
				if (e.key.code == sf::Keyboard::Space)
				{
					if (play.jump == false)
					{
						play.jump = true;
					}
				}
			}
		}
		if (e.type == sf::Event::KeyReleased)
		{
			if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::A)
			{
				play.left = false;
			}
			if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::D)
			{
				play.right = false;
			}
			if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::S)
			{
				play.down = false;
			}
			if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::W)
			{
				play.up = false;
			}
		}



		if (e.type == sf::Event::MouseButtonPressed) {
			if (e.mouseButton.button == sf::Mouse::Left) {

				setClickPos();
				if (isGUIOpen && mousedOverAGuiItem)
				{
					currentMousedOver->execute();
				}

				bool clickPosOnMinimap = (click.x / ts > minimapX && click.y / ts > minimapY && click.x / ts < minimapX + minimapWidth && click.y / ts < minimapY + minimapWidth);
				if (clickPosOnMinimap)
				{
					isMinimapExpanded = !isMinimapExpanded;
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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				ts += s;
			} 
			else
			{
				if (isBuildingWalls) 
				{
					if (elevationBuilding + s >= 0 && elevationBuilding + s < 4) {
						elevationBuilding += s;
					}
				}
				else
				{
					if (selectedInv + s >= 0 && selectedInv + s <= invTiles - 1)
					{
						selectedInv += s;
					}
				}
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
		if (play.inv.inv[selectedInv].id == 3)
		{
			setClickPos();
			buildingStickSecondary->x = (click.x / ts) + (camX);
			buildingStickSecondary->y = (click.y / ts) + (camY);
			buildingStickSecondary->bottom.elevation = 0;
			buildingStickSecondary->top.elevation = elevationBuilding;
			buildingStickSecondary->primary = false;
			buildingStickSecondary->otherhalves.push_back(buildingStickPrimary);
			if (isBuildingWalls)
			{
				std::shared_ptr<walls::Stick> stick1(new walls::Stick);
				std::shared_ptr<walls::Stick> stick2(new walls::Stick);
				stick2->x = buildingStickSecondary->x;
				stick2->y = buildingStickSecondary->y;
				bool secondDeleted = (stickmap.find(stick2->posKey()) != stickmap.end());

				stick1->id = walls::Stick::assignId();
				buildingStickSecondary->id = walls::Stick::assignId();
				stick1->bottom.elevation = 0;
				stick1->top.elevation = buildingStickPrimary->top.elevation;
				stick1->primary = true;
				stick1->x = buildingStickPrimary->x;
				stick1->y = buildingStickPrimary->y;

				stick1->mapped = false;
				stick2->mapped = false;
				if (!secondDeleted)
				{
					stick1->otherhalves.push_back(stick2);
				}
				bool firstDeleted = false;
				if (stickmap.find(stick1->posKey()) != stickmap.end())
				{
					firstDeleted = true;
					if (!secondDeleted)
					{
						stickmap[stick1->posKey()].otherhalves.push_back(stick2);
					}
					else
					{
						auto p2 = std::make_shared<walls::Stick>(stickmap[stick2->posKey()]);
						//p2->mapped = false;
						stickmap[stick1->posKey()].otherhalves.push_back(p2);
					}

				}
				else
				{
					stickmap[stick1->posKey()] = *stick1.get();
				}
				stick2->id = walls::Stick::assignId();
				stick2->bottom.elevation = 0;
				stick2->top.elevation = elevationBuilding;
				stick2->primary = false;

				if (!firstDeleted)
				{
					stick2->otherhalves.push_back(stick1);
				}
				else
				{
					auto p2 = std::make_shared<walls::Stick>(stickmap[stick1->posKey()]);
					stick2->otherhalves.push_back(p2);
				}
				if (stickmap.find(stick2->posKey()) != stickmap.end())
				{
					if (!firstDeleted)
					{
						stickmap[stick2->posKey()].otherhalves.push_back(stick1);
					}
					else
					{
						auto p2 = std::make_shared<walls::Stick>(stickmap[stick1->posKey()]);
						stickmap[stick2->posKey()].otherhalves.push_back(p2);
					}

				}
				else
				{
					stickmap[stick2->posKey()] = *stick2.get();
				}
			}
			isBuildingWalls = !isBuildingWalls;
			buildingStickPrimary->id = walls::Stick::assignId();
			buildingStickPrimary->x = (click.x/ts)+camX;
			buildingStickPrimary->y = (click.y / ts) + camY;
			buildingStickPrimary->bottom.elevation = 0;
			buildingStickPrimary->top.elevation = elevationBuilding;
			buildingStickPrimary->primary = true;
			buildingStickPrimary->otherhalves.push_back(buildingStickSecondary);
		}
	}

	void Game::draw()
	{
		sf::VertexArray mm(sf::Quads, 500);
		window.clear(sf::Color::Black);
		render(p);
		renderMinimap((isMinimapExpanded) ? minimapWidth : 5, (isMinimapExpanded) ? minimapX : minimapX + 15, (isMinimapExpanded) ? minimapY : minimapY + 15, &play, mm);
		window.draw(mm);
		moveGUIElements();
		renderUI();
		handleEvents();
		window.display();
	}

	void Game::moveGUIElements()
	{
		float xPrev = click.x;
		float yPrev = click.y;
		setClickPos();
		float xNow = click.x;
		float yNow = click.y;
		float xdiff = xNow - xPrev;
		float ydiff = yNow - yPrev;
		if (clickOnMinimap == true && !isGUIOpen)
		{
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
		return false;
	}
	bool Game::isMouseOver(int x, int y, int width, int height)
	{
		setClickPos();
		if (click.x >= x && click.x <= x + width && click.y >= y && click.y <= y + height)
		{
			return true;
		}
		return false;
	}

	void Game::renderUI()    
	{
		text.setOutlineThickness(0.0);
		text.setString(versionString);
		text.setPosition(sf::Vector2f(0, 0));
		text.setFillColor(sf::Color(255, 255, 255));
		window.draw(text);
		if (isGUIOpen)
		{
			std::vector<sf::Text> textToDrawAfterDone;
			sf::RectangleShape re;
			bool mouseOnSomething = false;
			for (gui::GUIContainer cont : gui::GUIController::getViewFromName(currentgui).containers)
			{
				//Draw the container
				re.setFillColor(sf::Color(0, 0, 0));
				re.setSize(sf::Vector2f(cont.width, cont.height));
				re.setPosition(sf::Vector2f(cont.x, cont.y));
				re.setOutlineColor(sf::Color::White);
				re.setOutlineThickness(5.0);
				window.draw(re);


				//Then draw each object
				int arbitraryPadding = 10;
				int index = 0;

				int currentX = arbitraryPadding;
				int currentY = arbitraryPadding;
				int prevObjWidth;

				for (std::shared_ptr<gui::GUIObject> obj : cont.objects)
				{
					re.setSize(sf::Vector2f(obj->width, obj->height));

					//we're going relative to the cont.y, so that is our 0 here

					int maximumY = cont.height-arbitraryPadding;
					//y increasing equates to DOWN
					if (currentY+obj->height > maximumY) { currentY = arbitraryPadding; currentX += prevObjWidth + arbitraryPadding; }


					sf::Vector2f pos(cont.x + currentX,
						cont.y + currentY);
					re.setPosition(pos);

					if (isMouseOver(&re))
					{
						mouseOnSomething = true;
						currentMousedOver = obj.get();
					}

					re.setOutlineThickness(0.0);
					re.setFillColor((isMouseOver(&re)) ? sf::Color(255, 255, 255) : sf::Color(100, 100, 100));
					window.draw(re);
					if (obj->needsSpecialRendering)
					{
						obj->render(pos.x, pos.y);
					}
					if (obj->text != "")
					{
						sf::Vector2f textpos(pos.x + (obj->width >> 1) - ((obj->text.size() >> 1)*((int)text.getCharacterSize())), pos.y + (obj->height >> 1) - ((int)text.getCharacterSize()>>1));
						text.setPosition(textpos);
						text.setString(obj->text);
						text.setOutlineThickness(0);
						text.setFillColor((isMouseOver(&re)) ? sf::Color(0, 0, 0) : sf::Color(255, 255, 255));
						window.draw(text);
					}
					if (obj->displayName && isMouseOver(&re))
					{
						setClickPos();
						text.setPosition(click + sf::Vector2f(17, 0));
						text.setString(obj->name);
						text.setOutlineThickness(5);
						text.setOutlineColor(sf::Color::Black);
						text.setFillColor(sf::Color::White);
						textToDrawAfterDone.push_back(text);
					}
					currentY += obj->height + arbitraryPadding;
					++index;
					prevObjWidth = obj->width;
				}
			}
			mousedOverAGuiItem = mouseOnSomething;
			if (mouseSlot.count != -1)
			{
				setClickPos();
				drawInventoryTileContent(mouseSlot.count, mouseSlot.thing, mouseSlot.thingWidth, mouseSlot.thingHeight, click.x, click.y);
			}
			for (sf::Text text : textToDrawAfterDone)
			{
				window.draw(text);
			}
		}
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
				drawInventoryTileContent(i, invX, invY);
			}
		}
	}
	void Game::drawInventoryTileContent(int i, int x, int y)
	{
		int wi = play.inv.inv[i].thingWidth;
		int he = play.inv.inv[i].thingHeight;
		std::string thing = play.inv.inv[i].thing;
		text.setFillColor(sf::Color::White);
		text.setString((sf::String)std::to_string(play.inv.inv[i].count));
		text.setPosition(sf::Vector2f(x + ts, y + ts + ts));
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		for (int h = 0; h < he; ++h)
		{
			for (int t = 0; t < wi; ++t)
			{
				char s = thing[(h * wi) + t];
				if (thing[s] != '0')
				{
					invItemRect.setFillColor(opixref[s]);
					invItemRect.setPosition(sf::Vector2f((x + ((1.5 / wi) * ts)) + (t * invItemRect.getSize().x), (y + ((1.5 / he) * ts)) + (h * invItemRect.getSize().y)));
					window.draw(invItemRect);
					window.draw(text);
				}
			}
		}
	}
	void Game::drawInventoryTileContent(int count, std::string thing, int width, int height, int x, int y)
	{
		text.setFillColor(sf::Color::White);
		text.setString((sf::String)std::to_string(count));
		text.setPosition(sf::Vector2f(x + ts, y + ts + ts));
		text.setOutlineColor(sf::Color::Black);
		text.setOutlineThickness(2);
		for (int h = 0; h < height; ++h)
		{
			for (int t = 0; t < width; ++t)
			{
				char s = thing[(h * width) + t];
				if (thing[s] != '0')
				{
					invItemRect.setFillColor(opixref[s]);
					invItemRect.setPosition(sf::Vector2f((x + ((1.5 / width) * ts)) + (t * invItemRect.getSize().x), (y + ((1.5 / height) * ts)) + (h * invItemRect.getSize().y)));
					window.draw(invItemRect);
					window.draw(text);
				}
			}
		}
	}
	bool compareSAC(sopAndCoord s1, sopAndCoord s2)
	{
		return(s1.floorY < s2.floorY);
	}

	void Game::render(perlin p)
	{
		sf::VertexArray quads(sf::Quads, 31000);
		sf::VertexArray us(sf::Quads, 20);

		bool onOrOff = false;
		std::unordered_map<std::string, objs::ObjectBrick> opixmap;
		std::unordered_map<std::string, objs::PlayerPixel> screenumap;
		std::unordered_map<std::string, walls::Stick> buildstickmap;
		updateDropsAndAddToScreenBuffer(screenumap);
		
		if (isBuildingWalls)
		{
			setClickPos();
			buildingStickSecondary->x = (click.x / ts) + (camX);
			buildingStickSecondary->y = (click.y / ts) + (camY);
			buildingStickSecondary->bottom.elevation = 0;
			buildingStickSecondary->top.elevation = elevationBuilding;
			buildingStickSecondary->primary = false;
			buildstickmap[buildingStickPrimary->posKey()] = *buildingStickPrimary.get();
			buildstickmap[buildingStickSecondary->posKey()] = *buildingStickSecondary.get();
		}

		for (int j = oboverscan + height + camY + 1; j > -oboverscan + 0 + camY - 1; --j)
		{
			for (int i = -oboverscan + 0 + camX - 1; i < width + camX + 1 + oboverscan; ++i)
			{
				int floorX = std::floor(i);
				int floorY = std::floor(j);
				std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
				if (pmap.find(keySpot) != pmap.end())
				{
					addPlayerPixelsToBuffer(floorX, floorY, screenumap);
				}
				if (fomap.find(keySpot) != fomap.end())
				{
					addFixedObjectPixelsToBuffer(opixmap, floorY, floorX, p);
				}
				if (stickmap.find(keySpot) != stickmap.end() ||
					buildstickmap.find(keySpot) != buildstickmap.end())
				{
					drawSingleWallPixel(i, j, onOrOff, opixmap, buildstickmap);
				}
				decidePixelAndDrawIfWithinScreenBounds(quads, floorX, floorY, opixmap, screenumap, p, us);
			}
		}
		window.draw(quads);
		window.draw(us);
		drawAndUpdateParticles();
		processMouseClickedOnObjectPixel(opixmap);
		perlinZEffect++;
	}

	void Game::bufferthis(sf::RectangleShape& rec, sf::VertexArray& qs)
	{
		sf::Vertex v1(rec.getPosition());
		sf::Vertex v2(rec.getPosition() + sf::Vector2f(0,ts));
		sf::Vertex v3(rec.getPosition() + sf::Vector2f(ts, ts));
		sf::Vertex v4(rec.getPosition() + sf::Vector2f(ts, 0));
		//setting color
		v1.color = v2.color = v3.color = v4.color = rec.getFillColor();
		qs.append(v1);
		qs.append(v2);
		qs.append(v3);
		qs.append(v4);
	}

	void Game::bufferraw(sf::Vector2f pos, sf::VertexArray& qs, sf::Color col)
	{
		sf::Vertex v1(pos);
		sf::Vertex v2(pos + sf::Vector2f(0, ts));
		sf::Vertex v3(pos + sf::Vector2f(ts, ts));
		sf::Vertex v4(pos + sf::Vector2f(ts, 0));
		//setting color
		v1.color = v2.color = v3.color = v4.color = col;
		qs.append(v1);
		qs.append(v2);
		qs.append(v3);
		qs.append(v4);
	}
	void Game::bufferthisbig(sf::RectangleShape& rec, sf::VertexArray& qs)
	{
		sf::Vertex v1(rec.getPosition() + sf::Vector2f(-ts, -ts));
		sf::Vertex v2(rec.getPosition() + sf::Vector2f(-ts, ts<<1));
		sf::Vertex v3(rec.getPosition() + sf::Vector2f(ts<<1, ts<<1));
		sf::Vertex v4(rec.getPosition() + sf::Vector2f(ts<<1, -ts));
		//setting color
		v1.color = v2.color = v3.color = v4.color = rec.getFillColor();
		qs.append(v1);
		qs.append(v2);
		qs.append(v3);
		qs.append(v4);
	}

	void Game::decidePixelAndDrawIfWithinScreenBounds(sf::VertexArray& qs, int i, int j, std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::unordered_map<std::string, objs::PlayerPixel>& screenumap, perlin& p, sf::VertexArray& us)
	{


		std::string keySpot = "" + std::to_string(i) + ',' + std::to_string(j);
		if (i > camX - 1 && i < width + camX + 1 && j > 0 + camY - 1 && j < height + camY + 1)
		{
			int offsetForElevation = 0;
			int myOffsetForElev = 0;
			if (worldmap.find(keySpot) != worldmap.end())
			{
				offsetForElevation = worldmap.at(keySpot).elevation;
			}
			if (worldmap.find(play.posKey()) != worldmap.end())
			{
				myOffsetForElev = worldmap.at(play.posKey()).elevation;
			}
			bool isObjectPix = false;
			if (opixmap.find(keySpot) != opixmap.end())
			{
				rect.setFillColor(opixmap.at(keySpot).col);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				if (opixmap.at(keySpot).isReflection)
				{
					bufferthis(rect, qs);
				}
				else
				{
					bufferthis(rect, qs);
				}
				isObjectPix = true;
			}
			bool dontDrawBecauseOfPlayerPixel = false;
			if (screenumap.find(keySpot) != screenumap.end())
			{
				if (wallPixels.find(keySpot) == wallPixels.end())
				{
					if (opixmap.find(keySpot) == opixmap.end())
					{

						if (!screenumap.at(keySpot).us) {
							rect.setFillColor(screenumap.at(keySpot).col);
							rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
							bufferthis(rect, qs);
							dontDrawBecauseOfPlayerPixel = true;
						}
						else {
							bufferraw(sf::Vector2f((71.11*ts) + (screenumap.at(keySpot).skinX * ts), (33.88*ts) - (std::floor((int)(play.elevation * ts) >> 4)) - (myOffsetForElev * ts) + (screenumap.at(keySpot).skinY * ts)), us, screenumap.at(keySpot).col);
						}



					}
					else
					{
						if (opixmap.at(keySpot).oby-1 <= screenumap.at(keySpot).py - offsetForElevation + (play.height))
						{
							

							if (!screenumap.at(keySpot).us) {
								rect.setFillColor(screenumap.at(keySpot).col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								bufferthis(rect, qs);
								dontDrawBecauseOfPlayerPixel = true;
							}
							else {
								bufferraw(sf::Vector2f((71.11 * ts) + (screenumap.at(keySpot).skinX * ts), (33.88 * ts) - (std::floor((int)(play.elevation * ts) >> 4)) - (myOffsetForElev * ts) + (screenumap.at(keySpot).skinY * ts)), us, screenumap.at(keySpot).col);
							}

						}
						else if (!opixmap.at(keySpot).isReflection)
						{
							rect.setFillColor(opixmap.at(keySpot).col);
							rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
							bufferthis(rect, qs);
						}
					}
				}
				else
				{
					if (opixmap.find(keySpot) == opixmap.end())
					{
						if (wallPixels.at(keySpot)->wallY >= screenumap.at(keySpot).py)
						{
							rect.setFillColor(wallPixels.at(keySpot)->myColor);
							rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
							bufferthis(rect, qs);
						}
						else
						{

							if (!screenumap.at(keySpot).us) {
								rect.setFillColor(screenumap.at(keySpot).col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								bufferthis(rect, qs);
								dontDrawBecauseOfPlayerPixel = true;
							}
							else {
								bufferraw(sf::Vector2f((71.11 * ts) + (screenumap.at(keySpot).skinX * ts), (33.88 * ts) - (std::floor((int)(play.elevation * ts) >> 4)) - (myOffsetForElev * ts) + (screenumap.at(keySpot).skinY * ts)), us, screenumap.at(keySpot).col);
							}

						}

					}
					else
					{
						if (opixmap.at(keySpot).oby - offsetForElevation <= screenumap.at(keySpot).py + offsetForElevation)
						{
							if (wallPixels.at(keySpot)->wallY <= screenumap.at(keySpot).py + offsetForElevation)
							{

								if (!screenumap.at(keySpot).us) {
									rect.setFillColor(screenumap.at(keySpot).col);
									rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
									bufferthis(rect, qs);
									dontDrawBecauseOfPlayerPixel = true;
								}
								else {
									bufferraw(sf::Vector2f((71.11 * ts) + (screenumap.at(keySpot).skinX * ts), (33.88 * ts) - (std::floor((int)(play.elevation * ts) >> 4)) - (myOffsetForElev * ts) + (screenumap.at(keySpot).skinY * ts)), us, screenumap.at(keySpot).col);
								}

							}
							else
							{
								rect.setFillColor(wallPixels.at(keySpot)->myColor);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								bufferthis(rect, qs);
							}
							
						}
						else if (!opixmap.at(keySpot).isReflection)
						{
							if (wallPixels.at(keySpot)->wallY <= opixmap.at(keySpot).oby + offsetForElevation)
							{
								rect.setFillColor(opixmap.at(keySpot).col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								bufferthis(rect, qs);
							}
							else
							{
								rect.setFillColor(wallPixels.at(keySpot)->myColor);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								bufferthis(rect, qs);
							}
							
						}
					}
				}
			}
			
			if (wallPixels.find(keySpot) != wallPixels.end() && !isObjectPix && !dontDrawBecauseOfPlayerPixel)
			{
				rect.setFillColor(wallPixels.at(keySpot)->myColor);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				bufferthis(rect, qs);
			}
			else if (wallPixels.find(keySpot) != wallPixels.end() && isObjectPix && !dontDrawBecauseOfPlayerPixel)
			{
				if (wallPixels.at(keySpot)->wallY <= opixmap.at(keySpot).oby+offsetForElevation)
				{
					rect.setFillColor(opixmap.at(keySpot).col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					bufferthis(rect, qs);
				}
				else
				{
					rect.setFillColor(wallPixels.at(keySpot)->myColor);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					bufferthis(rect, qs);
				}
			}
			else if (worldmap.find(keySpot) != worldmap.end() && isObjectPix == false && !dontDrawBecauseOfPlayerPixel)
			{
				if (worldmap.at(keySpot).col.a > 0)
				{
					rect.setFillColor(worldmap.at(keySpot).col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					bufferthis(rect, qs);
				}
				else
				{
					int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + ((int)perlinZEffect >> 8)) * 10);
					int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + ((int)perlinZEffect >> 4)) * 4);
					int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
					float waterLight = std::max(worldmap.at(keySpot).elevation, 0.0f) * 10;
					sf::Color col;
					col.r = (1 * n2Clamped + 1 + (waterLight * 5));
					col.g = (15 + n2Clamped + (waterLight * 5) + (15 * n2Clamped));
					col.b = (14 + (n2Clamped * 2) + (15 * n2Clamped) + (waterLight * 5));
					col.a = 105;
					rect.setFillColor(col);
					rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
					bufferthis(rect, qs);
				}
			}
			else if (isObjectPix == false && !dontDrawBecauseOfPlayerPixel)
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
				bufferthis(rect, qs);
			}
		}
	}

	void Game::renderMinimap(int widt, int x, int y, objs::Player* pla, sf::VertexArray& m)
	{
		int revScale = 20;
		for (int j = y; j < y + widt; j++)
		{
			for (int i = x; i < x + widt; i++)
			{
				int localX = (int)(pla->x + ((i - x) * revScale) - ((widt * revScale) >> 1));
				int localY = (int)(pla->y + ((j - y) * revScale) - ((widt * revScale) >> 1));
				std::string keySpot = "" + std::to_string(localX) + ',' + std::to_string(localY);
				if (worldmap.find(keySpot) != worldmap.end())
				{
					if (worldmap.at(keySpot).isWater != true)
					{
						rect.setFillColor(worldmap.at(keySpot).col);
						rect.setPosition(sf::Vector2f(i * ts, j * ts));
						bufferthis(rect, m);
					}
					else
					{
						rect.setFillColor(sf::Color::Blue);
						rect.setPosition(sf::Vector2f(i * ts, j * ts));
						bufferthis(rect, m);
					}
				}
			}
		}
	}
	void Game::handleEvents()
	{
		if (play.left)
		{
			camX -= play.movementSpeed;
			play.move(-play.movementSpeed, 0, &pmap);
		}
		if (play.right)
		{
			camX += play.movementSpeed;
			play.move(play.movementSpeed, 0, &pmap);
		}
		if (play.down)
		{
			camY += play.movementSpeed;
			play.move(0, play.movementSpeed, &pmap);
		}
		if (play.up)
		{
			camY -= play.movementSpeed;
			play.move(0, -play.movementSpeed, &pmap);
		}
	}
}