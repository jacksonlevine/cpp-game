#pragma once
#include "GUIObjects.h"
#include <unordered_map>
#include <string>

namespace gui
{
	class GUIController
	{
	private:
		static std::unordered_map<std::string, gui::GUIView> views;
	public:
		bool viewExists(std::string name);
		GUIView getViewFromName(std::string name);
		void setViews(std::unordered_map<std::string, gui::GUIView> newViews);
	};
}