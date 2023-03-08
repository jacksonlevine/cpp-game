#pragma once
#include <string>
#include <unordered_map>
#include "SFML/Graphics.hpp"
#include <chrono>
namespace objs
{
  int clamp(int val, int min, int max);
	class ColorBrick
	{
	public:
		sf::Color col;
		float elevation;
		bool isWater;
		ColorBrick(sf::Color c, float elev);
	};
	class FixedObject
	{
	public:
		int width;
		int height;
		int type;
		int x;
		int y;
		int strength;
		std::string thing;
		FixedObject();
		FixedObject(std::string thi, int wi, int he, int ty);
		void clickEvent();
	};
	class Chest : public FixedObject
	{
	public:
		Chest();
	};
	class DroppedItem
	{
	public:
		bool markedForDeletion;
		float x;
		float y;
		std::string name;
		int width;
		int height;
		float elevation;
		float PI;
		float angle;
		float x1;
		float y1;
		float r;
		int id;
		float timeStarted;
		float speedX;
		float speedY;
		float yTravel;
		float maxYTravel;
		std::string thing;
		DroppedItem(float ax, float ay, int i);
		void update();
	};
	bool operator==(const DroppedItem& a, const DroppedItem& b);
	class Particle
	{
	public:
		int life;
		int timer;
		float x;
		float y;
		sf::Color col;
		float speedX;
		float speedY;
		float yTravel;
		float maxYTravel;
		Particle();
		void update();
	};
	bool operator==(const Particle& x, const Particle& y);
  class ObjectBrick
	{
  public:
    sf::Color col;
		int obx;
		int oby;
		float elevation;
		objs::FixedObject* point;
		ObjectBrick();
		ObjectBrick(sf::Color c, int ox, int oy);
  };
	float getRandom();
  class PlayerPixel
	{
  public:
    sf::Color col;
    int px;
    int py;
		PlayerPixel();
		PlayerPixel(sf::Color c, int x, int y);
  };

	class InventorySlot
	{
	public:
		int id;
		int count;
		std::string thing;
		int thingWidth;
		int thingHeight;
		InventorySlot();
	};
	class Inventory
	{
	public:
		static const int size = 35;
		InventorySlot inv[size];
		Inventory();
		int findItem(int id);
		int firstOpenSlot();
	};
	class Player
	{
		std::string name;
		public:
			Inventory inv;
			float x;
			float y;
			int width;
			int height;
			bool jump;
			float elevation;
			float gravityForce;
			int jumpForce;
			bool left;
			bool right;
			bool up;
			bool down;
			float movementSpeed;
			Player();
			Player(std::string pname, int px, int py);
			Player(std::string pname, int px, int py, int wid, int hei);
			std::string posKey();
			void move(float mx, float my, std::unordered_map<std::string, Player*>* pmap);
			void stepJump();
	};
	class Tree
	{
	public:
		static std::string makeTree();
	};
	class Rock
	{
	public:
		static std::string makeRock();
	};
}