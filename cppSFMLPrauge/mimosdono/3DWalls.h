#pragma once
#include <string>
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
namespace walls
{
	class Point
	{
	public:
		float elevation;
		Point();
		Point(float e);
	};

	class Stick
	{
	public:
		static int currentId;
		int id;
		int x;
		int y;
		Point bottom;
		Point top;
		std::vector<std::shared_ptr<Stick>> otherhalves;
		bool primary;
		std::string posKey();
		bool operator== (const Stick& other);
		static int assignId();
	};

	class WallPixel
	{
	public:
		int wallY;
		sf::Color myColor;
		std::weak_ptr<WallPixel> pixelBehindMe;

	};


}