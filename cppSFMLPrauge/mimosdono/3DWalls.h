#pragma once
#include <string>

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
		Stick* otherhalf;
		bool primary;
		std::string posKey();
	};


}