#include "SFML/Graphics/RenderStates.hpp";
#include "perlin.h"
#include "perlin.cpp"
#include "JacksObjects.h"
#include <iostream>
sf::RenderWindow window(sf::VideoMode(1280, 720), "Window");
std::unordered_map<std::string, objs::ColorBrick> worldmap;
std::unordered_map<std::string, objs::FixedObject> fomap;
std::unordered_map<std::string, objs::ObjectBrick> opixmap;
std::unordered_map<std::string, objs::Player*> pmap;
std::unordered_map<char, sf::Color> opixref;
std::vector<std::string> mappedfos;
std::vector<objs::Particle> parts;
void render(perlin p);
void renderMinimap(int width, int x, int y, objs::Player*pla);
void handleEvents(objs::Player* pla);
void generateWorld(std::unordered_map<std::string, objs::ColorBrick>* wmap, perlin p);
void insertIntoWorld(int x, int y, float red, float green, float blue, float a, float elevation, std::unordered_map<std::string, objs::ColorBrick>* wmap, objs::ColorBrick brick);

float camX = 0;
float camY = 0;
int ws = 500;
int ts = 11;
sf::Vector2f click(-1, -1);

int width;
int height;

objs::Player play("Player1", (window.getSize().x / ts) / 2, (window.getSize().y / ts) / 2);
int main() 
{
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

	perlin p;
	sf::Event e;

	sf::Vector2u size = window.getSize();
	width = size.x / ts;
	height = size.y / ts;
	
	pmap[play.posKey()] = &play;

	generateWorld(&worldmap, p);
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			sf::Vector2i pos = sf::Mouse::getPosition(window);
			if (e.type == sf::Event::MouseButtonPressed) {
				click.x = pos.x;
				click.y = pos.y;
			}
			else {
				click.x = -1;
				click.y = -1;
			}

			if (e.type == sf::Event::Closed) 
			{
				window.close();
			}
		}
		window.clear(sf::Color::Black);
		render(p);
		renderMinimap(17, 90, 40, &play);
		handleEvents(&play);
		window.display();
	}
	
	return 0;
}
bool test = false;

double perlz = 0;

sf::RectangleShape rect(sf::Vector2f(ts, ts));

void render(perlin p) {
	std::unordered_map<std::string, objs::PlayerPixel> screenumap;
	double currOffsetX = 0.0;
	double currOffsetY = 0.0;
	int playSpotX = 0;
	int playSpotY = 0;
	for (int j = height+camY+1; j > 0+camY-1; j--) 
	{
		for (int i = 0+camX-1; i < width+camX+1; i++) 
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
				int elevOs = std::floor(pmap.at(keySpot)->elevation / 5);
				if (pmap.at(keySpot)->jump == true) {
					pmap.at(keySpot)->stepJump();
				}
					for (int a = 0 + yoff + std::max(yshrink-elevOs, 0) + elevOs; a < pmap.at(keySpot)->height + yoff + elevOs; a++)
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
				if (fomap.at(keySpot).strength < 0) {
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
					mappedfos.push_back(keySpot);
					justObj = true;
					objs::FixedObject* fop = &fomap.at(keySpot);
						int wi = fop->width;
						int he = fop->height;
						for (int f = 0; f < he; f++) {
							for (int o = 0; o < wi; o++) {
								char t = fop->thing[objs::clamp((f * wi) + o, 0, (wi * he) - 2)];
								if (t != '0') {
									std::string thisKeySpot = "" + std::to_string(floorX + o - (int)(wi / 2)) + ',' + std::to_string(floorY + f - he);
									objs::ObjectBrick ob(opixref[t], fop->x, fop->y);
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
				rect.setFillColor(worldmap.at(keySpot).col);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				window.draw(rect);
			}
			else if(justObj == false && isObjectPix == false  && std::abs(i) < ws && std::abs(j) < ws)
			{

				int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + (perlz / 500)) * 10);
				int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + (perlz / 300)) * 4);
				int n2Clamped = (std::min(std::max(n22-n32-4, 0), 8))%4;
				sf::Color col;
				col.r = (15 * n2Clamped+1);
				col.g = (15 * n2Clamped );
				col.b = (90+(n2Clamped*2));
				col.a = 255;
				rect.setFillColor(col);
				rect.setPosition(sf::Vector2f((i - camX) * ts, (j - camY) * ts));
				window.draw(rect);
			}
			else if(justObj == false && isObjectPix == false){
				int n22 = std::floor(p.noise(i * 2.1, j * 0.2, 11.01 + (perlz / 500)) * 10);
				int n32 = std::floor(p.noise(i * 5.1, j * 0.4, 11.01 + (perlz / 300)) * 4);
				int n2Clamped = (std::min(std::max(n22 - n32 - 4, 0), 8)) % 4;
				sf::Color col;
				col.r = (15 * n2Clamped + 1);
				col.g = (15 * n2Clamped );
				col.b = (90 + (n2Clamped * 2));
				col.a = 255;
				rect.setFillColor(col);
				rect.setPosition(sf::Vector2f((i - camX)* ts, (j - camY)* ts));
				window.draw(rect);
			}
		}
	}
	int pCount = parts.size();
	for (int i = 0; i < pCount; i++) {
		parts[i].update();
		rect.setPosition(sf::Vector2f((parts[i].x-camX)*ts, (parts[i].y-camY)*ts));
		rect.setFillColor(parts[i].col);
		window.draw(rect);
		if (parts[i].timer > parts[i].life) {
			parts.erase(std::remove(parts.begin(), parts.end(), parts[i]), parts.end());
		}
	}
	if (click.x != -1) {

		std::string keySpot = "" + std::to_string(((int)std::round(click.x)/ts)+(int)camX) + ',' + std::to_string(((int)std::round(click.y)/ts) + (int)camY);
		if (opixmap.find(keySpot) != opixmap.end()) {
			opixmap.at(keySpot).point->clickEvent();
			for (int n = 0; n < 1; n++) {
				objs::Particle pa;
				pa.x = (((int)std::round(opixmap.at(keySpot).obx - ((opixmap.at(keySpot).point->width/2)*((float)std::rand()/RAND_MAX)) + opixmap.at(keySpot).point->width/4)) );
				pa.y = ((int)std::round(opixmap.at(keySpot).oby - ((opixmap.at(keySpot).point->height/1.5) * ((float)std::rand() / RAND_MAX))));
				sf::Color c = opixmap.at(keySpot).col;
				c.r += 50;
				c.g += 50;
				c.b += 50;
				pa.col = c;
				parts.push_back(pa);
			}
		}
		click.x = -1;
		click.y = -1;
	}
	perlz++;
}

void renderMinimap(int width, int x, int y, objs::Player* pla) {
	int revScale = 10;
	for (int j = y; j < y + width; j++) {
		for (int i = x; i < x + width; i++) {
			int localX = (int)(pla->x + ((i-x) * revScale) - ((width*revScale)/2));
			int localY = (int)(pla->y + ((j-y) * revScale) - ((width*revScale)/2));
			std::string keySpot = "" + std::to_string(localX) + ',' + std::to_string(localY);
			if (worldmap.find(keySpot) != worldmap.end()) {
				rect.setFillColor(worldmap.at(keySpot).col);
				rect.setPosition(sf::Vector2f(i*ts, j*ts));
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
	for (int j = -ws; j < ws; j++) 
	{
		for (int i = -ws; i < ws; i++) 
		{
			double n = p.noise(i * 0.02, j * 0.02, 11.01) * 10;
			double n2 = p.noise(i * 0.05, j * 0.05, 11.01) * 4;
			double n3 = p.noise(i * 0.01, j * 0.01, 11.01) * 4;
			double n4 = p.noise(i * 0.9, j * 0.9, 11.01)/2;
			double n5 = p.noise(i * 0.009, j * 0.009, 7.01) * 15;
			double ln = (p.noise(i * 0.02, j * 0.02, 93.0122) * 10) + (n4*2);
			double nClamped = std::min(std::min(n5+ std::max(n+std::max(n3-2-n2, 0.0), 0.0), 10.0), 4.5) + std::max(n4, 0.0);
			int floorX = std::floor(i);
			int floorY = std::floor(j);
			std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
			int sandLvl = 2.8;
			float waterLvl = 0.6;
			
			if (nClamped > waterLvl && nClamped < sandLvl) {
				float red = (25 +320 * (nClamped / 10));
				float green = (20 + 310 * (nClamped/10));
				float blue = (237 * (nClamped / 10));
				float a = (255);
				float elev = nClamped;
				insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);
			}
			else if (nClamped > sandLvl) 
			{
				if (ln < 4.5) {
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
						std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
						fomap[keySpot] = rock;
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
						std::string keySpot = "" + std::to_string(floorX) + ',' + std::to_string(floorY);
						fomap[keySpot] = tree;
					}
					insertIntoWorld(floorX, floorY, red, green, blue, a, elev, wmap, brick);

				}
				
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
