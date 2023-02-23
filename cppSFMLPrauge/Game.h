#pragma once
//#include <SFML/Graphics/RenderStates.hpp>
#include "perlin.h"
#include "perlin.cpp"
#include "JacksObjects.h"
#include <iostream>
sf::RenderWindow window(sf::VideoMode(1280, 720), "Window");
sf::Font font;
namespace jl {
	class Game {
	public:

		std::unordered_map<std::string, objs::ColorBrick> worldmap;
		std::unordered_map<std::string, objs::FixedObject> fomap;
		std::unordered_map<std::string, objs::Player*> pmap;
		std::unordered_map<char, sf::Color> opixref;

		std::vector<objs::Particle> parts;
		std::vector<objs::DroppedItem> drops;

		float camX = 0;
		float camY = 0;
		int ws = 500;
		int ts = 11;
		sf::Vector2f click;
		bool mouseClicked = false;
		float clickTimer = 0;
		int clickInterval = 10;

		int selectedInv = 0;

		int width;
		int height;

		int minimapX = 90;
		int minimapY = 40;
		int minimapWidth = 17;

		objs::Player play;
		sf::Vector2u size;

		int invTiles = 5;
		int invTileSpacing = (int)((float)(minimapWidth * ts) / invTiles) + (int)((float)ts / invTiles);
		int invY = (minimapY * ts) + (minimapWidth * ts) + 10;
		sf::RectangleShape invRect;
		sf::RectangleShape invItemRect;
		perlin p;
		bool test = false;

		double perlz = 0;
		sf::Text text;

		sf::RectangleShape rect;
		Game() {
			click = sf::Vector2f(-1, -1);
			play = objs::Player("Player1", (window.getSize().x / ts) / 2, (window.getSize().y / ts) / 2);
			invRect = sf::RectangleShape(sf::Vector2f((int)invTileSpacing - 7, (int)invTileSpacing - 7));
			invItemRect = sf::RectangleShape(sf::Vector2f(7, 7));
			invRect.setFillColor(sf::Color(0, 0, 0));
			invItemRect.setFillColor(sf::Color(255, 255, 255));
			rect = sf::RectangleShape(sf::Vector2f(ts, ts));
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


			size = window.getSize();
			width = size.x / ts;
			height = size.y / ts;
			pmap[play.posKey()] = &play;
			generateWorld(&worldmap, p);

			// Load it from a file
			if (!font.loadFromFile("Akilvan.otf"))
			{
				std::cout << "Failed to load font";
			}
			// Create a text which uses our font
			text.setFont(font);
			text.setCharacterSize(15);
			text.setFillColor(sf::Color::White);
			text.setStyle(sf::Text::Regular);

		};
		void pollEvents(sf::Event e) {
			if (e.type == sf::Event::MouseButtonPressed) {
				if (e.mouseButton.button == sf::Mouse::Left) {
					setClickPos();
					mouseClicked = true;
					clickTimer = 0;
				}
				if (e.mouseButton.button == sf::Mouse::Right) {
					setClickPos();
					objs::ColorBrick b(sf::Color(50,50,50), 10);
					insertIntoWorld((int)(click.x / ts + camX), (int)(click.y / ts + camY), 50, 50, 50, 255, 10, &worldmap, b);
				}
			}

			if (e.type == sf::Event::MouseButtonReleased) {
				mouseClicked = false;
			}

			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			if (e.type == sf::Event::MouseWheelScrolled)
			{
				int s = (int)e.mouseWheelScroll.delta;
				if (selectedInv + s >= 0 && selectedInv + s <= invTiles - 1) {
					selectedInv += s;
				}
			}
		}

		void draw() {
			window.clear(sf::Color::Black);
			render(p);
			renderMinimap(minimapWidth, minimapX, minimapY, &play);
			renderUI();
			handleEvents(&play);
			window.display();
		}

		void setClickPos() {
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			float xRatio = (float)size.x / (float)window.getViewport(window.getView()).width;
			float yRatio = (float)size.y / (float)window.getViewport(window.getView()).height;
			click.x = (int)std::round(pos.x * xRatio);
			click.y = (int)std::round(pos.y * yRatio);
		}

		bool isMouseOver(sf::RectangleShape* recto) {
			setClickPos();
			sf::Vector2f rectPos = recto->getPosition();
			sf::Vector2f rectSize = recto->getSize();
			if (click.x >= rectPos.x && click.x <= rectPos.x + rectSize.x && click.y >= rectPos.y && click.y <= rectPos.y + rectSize.y) {
				return true;
			}
			else {
				return false;
			}
		}

		void renderUI() {
			text.setString("MimosDono Alpha v12.0.0");
			text.setPosition(sf::Vector2f(0,0));
			window.draw(text);
			for (int i = 0; i < invTiles; i++) {
				int invX = (minimapX * ts) + (i * invTileSpacing);
				invRect.setPosition(sf::Vector2f(invX, invY));
				invRect.setFillColor((isMouseOver(&invRect) || selectedInv == i) ? sf::Color(50, 50, 50) : sf::Color(0, 0, 0));
				if (selectedInv == i) {
					invRect.setOutlineColor(sf::Color(255, 255, 255));
					invRect.setOutlineThickness(2);
				}
				else {
					invRect.setOutlineThickness(0);
				}

				window.draw(invRect);
				if (play.inv.inv[i].id != -1) {
					int wi = play.inv.inv[i].thingWidth;
					int he = play.inv.inv[i].thingHeight;
					std::string thing = play.inv.inv[i].thing;
					text.setString((sf::String)std::to_string(play.inv.inv[i].count));
					text.setPosition(sf::Vector2f(invX + ts, invY+ts+ts));
					text.setOutlineColor(sf::Color::Black);
					text.setOutlineThickness(2);
					for (int h = 0; h < he; h++) {
						for (int t = 0; t < wi; t++) {
							char s = thing[(h * wi) + t];
							if (thing[s] != '0') {
								invItemRect.setFillColor(opixref[s]);
								invItemRect.setPosition(sf::Vector2f((invX+((1.5/wi)*ts)) + (t * invItemRect.getSize().x), (invY + ((1.5 / he)*ts)) + (h * invItemRect.getSize().y)));
								window.draw(invItemRect);
								window.draw(text);
							}
							
						}
					}
				}
			}
		}

		std::unordered_map<std::string, int> typeID = { {"stone", 0},{"wood", 1},{"no texture", 2} };
		int oboverscan = 20;

		void render(perlin p) {

			std::unordered_map<std::string, objs::ObjectBrick> opixmap;
			std::vector<std::string> mappedfos;
			std::unordered_map<std::string, objs::PlayerPixel> screenumap;
			double currOffsetX = 0.0;
			double currOffsetY = 0.0;
			int playSpotX = 0;
			int playSpotY = 0;
			int dCount = drops.size();
			for (int i = 0; i < dCount; i++) {
				drops[i].update();
				int range = 20;
				if ((drops[i].x - play.x) < range && (drops[i].y - play.y) < range && (drops[i].x - play.x) > -range && (drops[i].y - play.y) > -range) {
					drops[i].x += (play.x - drops[i].x) / 10;
					drops[i].y += (play.y - drops[i].y) / 10;
					if ((drops[i].x - play.x) < 1 && (drops[i].y - play.y) < 1 && (drops[i].x - play.x) > -1 && (drops[i].y - play.y) > -1) {
						if (typeID.find(drops[i].name) != typeID.end()) {
							int found = play.inv.findItem(typeID.at(drops[i].name));
							int fos = play.inv.firstOpenSlot();
							if (found != -1) {
								play.inv.inv[found].count += 1;
							}
							else if (fos != -1) {
								play.inv.inv[fos].id = typeID.at(drops[i].name);
								play.inv.inv[fos].count = 1;
								play.inv.inv[fos].thing = drops[i].thing;
								play.inv.inv[fos].thingWidth = drops[i].width;
								play.inv.inv[fos].thingHeight = drops[i].height;
							}
							if (found != -1 || fos != -1) {
								drops[i].markedForDeletion = true;
							}
						}
					}
				}
				int wi = drops[i].width;
				int he = drops[i].height;
				for (int h = 0; h < he; h++) {
					for (int w = 0; w < wi; w++) {
						std::string thisKeySpot = "" + std::to_string((int)(drops[i].x + w)) + ',' + std::to_string((int)((float)drops[i].y + h + ((float)drops[i].elevation)));
						sf::Color c = opixref[drops[i].thing[objs::clamp((h * wi) + w, 0, drops[i].thing.size() - 1)]];
						objs::PlayerPixel pi(c, drops[i].x + w, drops[i].y + h);
						if (drops[i].thing[objs::clamp((h * wi) + w, 0, drops[i].thing.size() - 1)] != '0') {
							screenumap[thisKeySpot] = pi;
						}
					}
				}
				if (drops[i].markedForDeletion == true) {
					std::erase(drops, drops[i]);
				}
			}
			for (int j = oboverscan + height + camY + 1; j > -oboverscan + 0 + camY - 1; j--)
			{
				for (int i = -oboverscan + 0 + camX - 1; i < width + camX + 1; i++)
				{
					int floorX = std::floor(i);
					int floorY = std::floor(j);
					std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
					if (pmap.find(keySpot) != pmap.end())
					{
						int yoff = 0;
						int yshrink = 0;
						if (worldmap.find(keySpot) != worldmap.end()) {
							yoff = std::floor(worldmap.at(keySpot).elevation);
						}
						else {
							yshrink = 2;
						}
						int elevOs = std::floor(pmap.at(keySpot)->elevation / 10);
						if (pmap.at(keySpot)->jump == true) {
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
					bool justObj = false;
					if (fomap.find(keySpot) != fomap.end()) {
						if (fomap.at(keySpot).strength < 0) {                            //BREAK OBJ
							int dropCount = (int)(((float)std::rand() / RAND_MAX) * 10);
							for (int n = 0; n < dropCount; n++) {

								float xOff = (int)(((float)std::rand() / RAND_MAX) * -7 + 3.5);
								float yOff = (int)(((float)std::rand() / RAND_MAX) * -5 + 2.5);

								objs::DroppedItem d(fomap.at(keySpot).x + xOff, fomap.at(keySpot).y + yOff, (int)drops.size());
								if (fomap.at(keySpot).type == 0) {
									d.thing = "tttttt";
									d.height = 2;
									d.width = 3;
									d.name = "wood";
									d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
								}
								else if (fomap.at(keySpot).type == 1) {
									d.thing = "00a0aasaasna0nna";
									d.height = 4;
									d.width = 4;
									d.name = "stone";
									d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
								}
								else {
									d.thing = "0a0ata0a0";
									d.width = 3;
									d.height = 3;
									d.name = "no texture";
									d.timeStarted = std::chrono::high_resolution_clock::now().time_since_epoch().count() + (std::rand() * 10000000);
								}

								drops.push_back(d);
							}
							for (int n = 0; n < 25; n++) {
								objs::Particle pa;
								pa.x = (((int)std::round(fomap.at(keySpot).x - ((fomap.at(keySpot).width / 2) * ((float)std::rand() / RAND_MAX)) + fomap.at(keySpot).width / 4)));
								pa.y = ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height / 1.5) * ((float)std::rand() / RAND_MAX))));
								sf::Color c = opixref[fomap.at(keySpot).thing[((fomap.at(keySpot).height - 1) * fomap.at(keySpot).width) + (int)(fomap.at(keySpot).width / 2)]];
								c.r += 50;
								c.g += 50;
								c.b += 50;
								pa.col = c;
								parts.push_back(pa);
							}
							fomap.erase(keySpot);
							mappedfos.clear();
							opixmap.clear();
						}
						else {
							if (std::find(mappedfos.begin(), mappedfos.end(), keySpot) == mappedfos.end()) {
								//mappedfos.push_back(keySpot);
								objs::FixedObject* fop = &fomap.at(keySpot);
								int wi = fop->width;
								int he = fop->height;
								for (int f = 0; f < he; f++) {
									for (int o = 0; o < wi; o++) {
										char t = fop->thing[objs::clamp((f * wi) + o, 0, (wi * he) - 2)];
										if (t != '0') {
											objs::ObjectBrick ob(opixref[t], fop->x, fop->y);
											ob.elevation = he - f;
											if (worldmap.find(keySpot) != worldmap.end()) {
												ob.elevation += worldmap.at(keySpot).elevation;
											}
											int difference = (((floorY)-(int)(play.y + 120)) * ob.elevation);
											int differenceX = (((floorX-35)-(int)play.x) * ob.elevation);
											int ksx = floorX + (int)((((o * 3) - 40) * ob.elevation + (differenceX/4)) / 50);
											int ksy = floorY + (int)(((f * 3) + (difference / 8)) / 10) / 2;
											std::string thisKeySpot = "" + std::to_string(ksx) + ',' + std::to_string(ksy);



											ob.point = fop;
											if (opixmap.find(thisKeySpot) == opixmap.end()) {
												if (ob.col == opixref['l'])
												{
													if ((float)std::rand() / RAND_MAX > 0.9999) 
													{
														objs::Particle pa;
														pa.x = (((int)std::round(fomap.at(keySpot).x - ((fomap.at(keySpot).width / 2) * ((float)std::rand() / RAND_MAX)) + fomap.at(keySpot).width / 4)));
														pa.y = ((int)std::round(fomap.at(keySpot).y - ((fomap.at(keySpot).height / 1.5) * ((float)std::rand() / RAND_MAX))));
														sf::Color c = opixref['l'];
														pa.speedY = std::max(pa.speedY, 0.1f);
														pa.speedX = ((float)std::rand() / RAND_MAX)-0.5f;
														pa.col = c;
														parts.push_back(pa);
													}
												}
												opixmap[thisKeySpot] = ob;


											}
											else {
												if (opixmap.at(thisKeySpot).oby < fop->y) {
													opixmap[thisKeySpot] = ob;


												}
											}
										}
									}
								}
								for (int f = he - 1; f > 0; f--) {
									for (int o = 0; o < wi; o++) {
										char t = fop->thing[objs::clamp((f * wi) + o, 0, (wi * he) - 2)];
										if (t != '0') {
											std::string thisKeySpot = "" + std::to_string(floorX + o - (int)(wi / 2)) + ',' + std::to_string(floorY - f + he);
											if (worldmap.find(thisKeySpot) != worldmap.end()) {
												if (worldmap.at(thisKeySpot).col.a < 1) {
													sf::Color c = opixref[t];
													c.b += 25;
													c.r = std::max(c.r - 25, 0);
													c.g = std::max(c.g - 55, 0);
													c.a = 255;
													objs::ObjectBrick ob(c, fop->x, fop->y);
													ob.point = fop;
													if (opixmap.find(thisKeySpot) == opixmap.end()) {
														opixmap[thisKeySpot] = ob;
													}
													else {
														if (opixmap.at(thisKeySpot).oby < fop->y) {
															opixmap[thisKeySpot] = ob;
														}
													}
												}
											}
										}
									}
								}
							}
						}

					}
					if (i > camX - 1 && i < width + camX + 1 && j > 0 + camY - 1 && j < height + camY + 1)
					{
							bool isObjectPix = false;
						if (opixmap.find(keySpot) != opixmap.end()) {

							rect.setFillColor(opixmap.at(keySpot).col);
							rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
							window.draw(rect);
							isObjectPix = true;
						}

						if (screenumap.find(keySpot) != screenumap.end() && justObj == false)
						{
							if (opixmap.find(keySpot) == opixmap.end()) {
								rect.setFillColor(screenumap.at(keySpot).col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								window.draw(rect);
							}
							else {
								if (opixmap.at(keySpot).oby < screenumap.at(keySpot).py) {
									rect.setFillColor(screenumap.at(keySpot).col);
									rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
									window.draw(rect);
								}
							}
						}
						else
						if (worldmap.find(keySpot) != worldmap.end() && justObj == false && isObjectPix == false)
						{
							if (worldmap.at(keySpot).col.a > 0) {
								rect.setFillColor(worldmap.at(keySpot).col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								window.draw(rect);
							}
							else {
								int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + (perlz / 500)) * 10);
								int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + (perlz / 300)) * 4);
								int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
								float waterLight = std::max(worldmap.at(keySpot).elevation, 0.0f) * 10;
								sf::Color col;
								col.r = (7 * n2Clamped + 1 + (waterLight * 5));
								col.g = (7 * n2Clamped + (waterLight * 5));
								col.b = (45 + (n2Clamped * 2) + (waterLight * 5));
								col.a = 255;
								rect.setFillColor(col);
								rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
								window.draw(rect);
							}

						}
						else if (justObj == false && isObjectPix == false) {
							int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + (perlz / 500)) * 10);
							int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + (perlz / 300)) * 4);
							int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
							sf::Color col;
							col.r = (15 * n2Clamped + 1);
							col.g = (15 * n2Clamped);
							col.b = (90 + (n2Clamped * 2));
							col.a = 255;
							rect.setFillColor(col);
							rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
							window.draw(rect);
						}
					}
				}
			}
			int pCount = parts.size();
			for (int i = 0; i < pCount; i++) {
				parts[i].update();
				rect.setPosition(sf::Vector2f((parts[i].x - camX) * ts, (parts[i].y - camY) * ts));
				rect.setFillColor(parts[i].col);
				window.draw(rect);
				if (parts[i].timer > parts[i].life) {
					parts.erase(std::remove(parts.begin(), parts.end(), parts[i]), parts.end());
				}
			}

			if (mouseClicked == true) {
				setClickPos();
				if (clickTimer <= 0.1) {
					clickTimer = clickInterval;
					std::string keySpot = "" + std::to_string(((int)std::round(click.x) / ts) + (int)camX) + ',' + std::to_string(((int)std::round(click.y) / ts) + (int)camY);
					if (opixmap.find(keySpot) != opixmap.end()) {
						opixmap.at(keySpot).point->clickEvent();

						for (int n = 0; n < 1; n++) {
							objs::Particle pa;
							pa.x = (((int)std::round(opixmap.at(keySpot).obx - ((opixmap.at(keySpot).point->width / 2) * ((float)std::rand() / RAND_MAX)) + opixmap.at(keySpot).point->width / 4)));
							pa.y = ((int)std::round(opixmap.at(keySpot).oby - ((opixmap.at(keySpot).point->height / 1.5) * ((float)std::rand() / RAND_MAX))));
							sf::Color c = opixmap.at(keySpot).col;
							c.r += 50;
							c.g += 50;
							c.b += 50;
							pa.col = c;
							parts.push_back(pa);

						}
					}

				}
				else {
					clickTimer -= 2;

				}
			}
			perlz++;
		}

		void renderMinimap(int widt, int x, int y, objs::Player* pla) {
			int revScale = 10;
			for (int j = y; j < y + widt; j++) {
				for (int i = x; i < x + widt; i++) {
					int localX = (int)(pla->x + ((i - x) * revScale) - ((widt * revScale) / 2));
					int localY = (int)(pla->y + ((j - y) * revScale) - ((widt * revScale) / 2));
					std::string keySpot = "" + std::to_string(localX) + ',' + std::to_string(localY);
					if (worldmap.find(keySpot) != worldmap.end()) {
						rect.setFillColor(worldmap.at(keySpot).col);
						rect.setPosition(sf::Vector2f(i * ts, j * ts));
						window.draw(rect);
					}
				}
			}
		}

		void handleEvents(objs::Player* pla) {
			float movement = 1;
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
				if (pla->jump == false) {
					pla->jump = true;
				}
			}
		}
		void generateWorld(std::unordered_map<std::string, objs::ColorBrick>* wmap, perlin p)
		{

			sf::Color col;
			objs::ColorBrick brick(col, 0);
			std::srand(std::time(0));
			float offset = ((float)std::rand() / RAND_MAX) * 10000000;
			for (int j = -ws; j < ws; j++)
			{
				for (int i = -ws; i < ws; i++)
				{

					double n = p.noise(i * 0.02, j * 0.02, 11.01 + offset) * 10;
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

					if (nClamped > waterLvl && nClamped < sandLvl) {
						float red = (25 + 320 * (nClamped / 10));
						float green = (20 + 310 * (nClamped / 10));
						float blue = (237 * (nClamped / 10));
						float a = (255);
						float elev = nClamped;
						insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);
					}
					else if (nClamped > sandLvl)
					{
						if (ln < 2) {
							float red = std::min(25 + 5 * (nClamped * 3), 204.5);
							float green = std::min(25 + 10 * (nClamped * 3), 204.5);
							float blue = (2 * (nClamped * 3));
							float a = (255);
							float elev = nClamped;
							insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);
							if (std::rand() > 32750) {
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
						else {
							float red = (25 + 17 * nClamped + (n4 * 100));
							float green = (25 + 10 * nClamped + (n4 * 100));
							float blue = (std::min(9 * nClamped + (n4 * 30), 50.0));
							float a = (255);
							float elev = nClamped;
							if (std::rand() > 32500) {
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
							insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);

						}

					}
					else {
						float red = (0);
						float green = (0);
						float blue = (0);
						float a = (0);
						float elev = nClamped;
						insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);
					}

				}
			}
		}
		void insertIntoWorld(int x, int y, float red, float green, float blue, float a, float elevation, std::unordered_map<std::string, objs::ColorBrick>* wmap, objs::ColorBrick brick) {
			brick.col.r = red;
			brick.col.g = green;
			brick.col.b = blue;
			brick.col.a = a;
			brick.elevation = elevation;
			std::string keySpot = "" + std::to_string(x) + ',' + std::to_string(y);
			wmap->insert_or_assign(keySpot, brick);
		}

	};
}