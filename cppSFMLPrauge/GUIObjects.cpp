#include "mimosdono/GUIObjects.h"
#include "mimosdono/Game.h"
#include <iostream>
namespace gui
{

	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
	}
	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string ro)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
		route = ro;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string te, std::string ro)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
		needsSpecialRendering = false;
		route = ro;
	}
	GUIInventorySlot::GUIInventorySlot(jl::Game* g, int wi, int he, int ind)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		needsSpecialRendering = true;
		mouseOver = false;
		myIndex = ind;
	}

	GUIPlayerViewer::GUIPlayerViewer(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		needsSpecialRendering = true;
		mouseOver = false;
	}


	void GUIQuitButton::execute()
	{
		_g->window.close();
	}
	void GUIRouteButton::execute()
	{
		_g->currentgui = route;
	}
	void GUICloseButton::execute()
	{
		_g->isGUIOpen = false;
	}
	void GUIInventorySlot::execute()
	{
		std::cout << "I am an inventory slot.";
	}
	void GUIPlayerViewer::execute()
	{
		std::cout << "I am a player viewer.";
	}

	void GUIInventorySlot::render(int x, int y)
	{
		_g->drawInventoryTileContent(myIndex, x, y);
	}

	void GUIPlayerViewer::render(int x, int y)
	{
		//render player  here;
	}

	GUIView::GUIView(jl::Game* g)
	{
		_g = g;
	}
	GUIView::GUIView()
	{

	}
	GUIContainer::GUIContainer(int i, int j, int wi, int he)
	{
		x = i;
		y = j;
		width = wi;
		height = he;
	}
	GUIContainer::GUIContainer()
	{
		height = 100;
		width = 100;
		x = 0;
		y = 0;
	}
}