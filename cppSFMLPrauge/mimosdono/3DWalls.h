#pragma once
#include <string>
#include <memory>
#include <vector>
#include "SFML/Graphics.hpp"
#include <optional>
namespace walls
{
	class Point
	{
	public:
		float elevation;
		Point();
		Point(float e);
	};

	class WallPixel
	{
	public:
		int wallY;
		sf::Color myColor;
		std::optional<std::weak_ptr<WallPixel>> pixelBehindMe;
		WallPixel(int y, sf::Color col, std::optional<std::weak_ptr<WallPixel>> behind);
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
		bool mapped;
		std::vector<std::shared_ptr<WallPixel>> myPixels;
		std::string posKey();
		bool operator== (const Stick& other);
		static int assignId();
	};




}