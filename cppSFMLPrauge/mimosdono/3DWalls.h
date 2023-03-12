#pragma once
#include <string>
#include <memory>
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
		int id;
		int x;
		int y;
		Point bottom;
		Point top;
		std::shared_ptr<Stick> otherhalf;
		bool primary;
		std::string posKey();
		bool operator== (const Stick& other);
	};


}