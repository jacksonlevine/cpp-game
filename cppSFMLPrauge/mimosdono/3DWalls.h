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
		int x;
		int y;
		Point bottom;
		Point top;
		std::shared_ptr<Stick> otherhalf;
		bool primary;
		std::string posKey();
	};


}