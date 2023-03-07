#include "mimosdono/GUIController.h"

namespace gui
{
	std::unordered_map<std::string, GUIView> GUIController::views;
	bool GUIController::viewExists(std::string name)
	{
		return (views.find(name) != views.end());
	}
	GUIView GUIController::getViewFromName(std::string name)
	{
		return views[name];
	}
	void GUIController::setViews(std::unordered_map<std::string, gui::GUIView> newViews)
	{
		views = newViews;
	}
}