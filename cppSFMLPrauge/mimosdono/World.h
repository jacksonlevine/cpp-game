#pragma once
#include "JacksObjects.h"
#include "Perlin.h"
namespace world
{
	class World
	{
	public:
		static std::unordered_map<std::string, objs::ColorBrick> generateWorld(perlin p, int ws, std::unordered_map<std::string, objs::FixedObject>& fomap);
		static void insertIntoWorld(int x, int y, float red, float green, float blue, float a, float elevation, std::unordered_map<std::string, objs::ColorBrick>* wmap, objs::ColorBrick brick);
		static std::unordered_map<char, sf::Color> getObjectPixReferences();
	};
}