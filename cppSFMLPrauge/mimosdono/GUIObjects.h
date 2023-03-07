#pragma once
#include "JacksObjects.h"
#include <vector>
#include "GUIObjects.h"

namespace gui
{
	class GUIObject
	{
	public:
		int relX;
		int relY;
	};

	class GUIContainer
	{
	public:
		int x;
		int y;
		int width;
		int height;
		std::vector<GUIObject> objects;
	};

	class GUIView
	{
	public:
		std::vector<GUIContainer> containers;
	};
}