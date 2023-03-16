#pragma once
#include "World.h"
#include "3DWalls.h"
#include <iostream>
namespace jl {
	class Game {
	public:
		std::string currentgui;
		bool isGUIOpen;
		bool isFullscreen;
		std::string versionString;
		bool mousedOverAGuiItem;
		bool guiKeyJustTriggered;
		bool isBuildingWalls;
		bool isMinimapExpanded;
		std::shared_ptr<walls::Stick> buildingStickPrimary;
		std::shared_ptr<walls::Stick> buildingStickSecondary;
		int gameWidth;
		int gameHeight;
		void addTestThingsToInventory();
		sf::RenderWindow window;
		sf::Font font;
		perlin p;
		std::unordered_map<std::string, objs::FixedObject> fomap;
		std::unordered_map<std::string, objs::ColorBrick> worldmap;
		std::unordered_map<std::string, walls::Stick> stickmap;
		std::unordered_map<char, sf::Color> opixref;
		std::unordered_map<std::string, objs::Player*> pmap;
		std::vector<objs::Particle> parts;
		std::vector<objs::DroppedItem> drops;
		float camX;
		float camY;
		int ws;
		int ts;
		sf::Vector2f click;
		bool mouseClicked;
		float clickTimer;
		int clickInterval;
		int selectedInv;
		int elevationBuilding;
		int width;
		int height;
		float minimapX;
		float minimapY;
		int minimapWidth;
		int invY;
		objs::Player play;
		sf::Vector2u size;
		int invTiles;
		int invTileSpacing;
		sf::RectangleShape invRect;
		sf::RectangleShape invItemRect;
		bool test;
		bool clickOnMinimap;
		bool clickPositionSet;
		double perlinZEffect;
		double perlinZEffect2;
		sf::Text text;
		int testNum;
		std::unordered_map<std::string, int> typeID;
		int oboverscan;
		sf::RectangleShape rect;
		sf::ConvexShape conv;
		Game();
		void pollEvents(sf::Event e);
		void placeCurrentItem();
		void draw();
		void moveGUIElements();
		void setClickPos();
		bool isMouseOver(sf::RectangleShape* recto);
		bool isMouseOver(int x, int y, int width, int height);
		void renderUI();
		void drawInventoryTileContent(int i, int invX);
		void render(perlin p);
		void drawAndUpdateParticles();
		void processMouseClickedOnObjectPixel(std::unordered_map<std::string, objs::ObjectBrick>& opixmap);
		void spawnParticleFromObjectPixel(std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::string& keySpot);
		void decidePixelAndDrawIfWithinScreenBounds(sf::VertexArray& qs, int i, int j, std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::unordered_map<std::string, objs::PlayerPixel>& screenumap, perlin& p);
		void addPlayerPixelsToBuffer(int floorX, int floorY, std::unordered_map<std::string, objs::PlayerPixel>& screenumap);
		void breakFixedObjectAndDropItems(std::string& keySpot);
		void addFixedObjectPixelsToBuffer( std::unordered_map<std::string, objs::ObjectBrick>& opixmap, int floorY, int floorX, perlin& p);
		void updateDropsAndAddToScreenBuffer(std::unordered_map<std::string, objs::PlayerPixel>& screenumap);
		void renderMinimap(int widt, int x, int y, objs::Player* pla);
		void handleEvents();

		void bufferthis(sf::RectangleShape& rec, sf::VertexArray& qs);
		void drawSingleWallPixel( int i, int j, bool onOrOff, std::unordered_map<std::string, objs::ObjectBrick>& opixmap, std::unordered_map<std::string, walls::Stick>& buildstickmap);
	};
	class sopAndCoord
	{
	public:
		walls::Stick* sop;
		int floorX;
		int floorY;
	};
}