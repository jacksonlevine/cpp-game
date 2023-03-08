#pragma once
#include "JacksObjects.h"
#include <vector>
#include "GUIObjects.h"

namespace gui
{
	class GUIObject
	{
	public:
		int width;
		int height;
		std::string text;
		GUIObject(int wi, int he);
		GUIObject(int wi, int he, std::string te);
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