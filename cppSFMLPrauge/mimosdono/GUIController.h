#pragma once
#include "Game.h"
#include "GUIObjects.h"
#include <unordered_map>
#include <string>

namespace gui
{
	class GUIController
	{
	public:
		static std::unordered_map<std::string, gui::GUIView> views;
		static bool viewExists(std::string name);
		static GUIView getViewFromName(std::string name);
		static void setViews(std::unordered_map<std::string, gui::GUIView> newViews);
	};
}