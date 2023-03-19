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
		name = "";
		_g = g;
		mouseOver = false;
		displayName = false;
		needsSpecialRendering = false;
	}
	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		name = "";
		mouseOver = false;
		displayName = false;
		needsSpecialRendering = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		name = "";
		mouseOver = false;
		displayName = false;
		needsSpecialRendering = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		name = "";
		mouseOver = false;
		displayName = false;
		needsSpecialRendering = false;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string ro)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		name = "";
		mouseOver = false;
		displayName = false;
		needsSpecialRendering = false;
		route = ro;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string te, std::string ro)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		name = "";
		mouseOver = false;
		displayName = false;
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
		displayName = true;
		mouseOver = false;
		myIndex = ind;
		name = _g->play.inv.inv[myIndex].name; //update the gui object's name
	}

	GUIPlayerViewer::GUIPlayerViewer(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		name = "";
		needsSpecialRendering = true;
		mouseOver = false;
		displayName = false;
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
		if (_g->mouseSlot.count == -1 && _g->play.inv.inv[myIndex].count != -1) //if the mouse is empty and the slot has something
		{
			_g->mouseSlot.id = _g->play.inv.inv[myIndex].id;
			_g->mouseSlot.count = _g->play.inv.inv[myIndex].count;
			_g->mouseSlot.thing = _g->play.inv.inv[myIndex].thing;
			_g->mouseSlot.thingWidth = _g->play.inv.inv[myIndex].thingWidth;
			_g->mouseSlot.thingHeight = _g->play.inv.inv[myIndex].thingHeight;
			_g->mouseSlot.name = _g->play.inv.inv[myIndex].name;
			_g->play.inv.inv[myIndex].id = -1;
			_g->play.inv.inv[myIndex].count = -1;
			_g->play.inv.inv[myIndex].thing = "";
			_g->play.inv.inv[myIndex].thingWidth = 0;
			_g->play.inv.inv[myIndex].thingHeight = 0;
			_g->play.inv.inv[myIndex].name = "";
		}
		else if (_g->mouseSlot.count != -1 && _g->play.inv.inv[myIndex].count == -1) //if the mouse has something and the slot is empty
		{
			_g->play.inv.inv[myIndex].id = _g->mouseSlot.id;
			_g->play.inv.inv[myIndex].count = _g->mouseSlot.count;
			_g->play.inv.inv[myIndex].thing = _g->mouseSlot.thing;
			_g->play.inv.inv[myIndex].thingWidth = _g->mouseSlot.thingWidth;
			_g->play.inv.inv[myIndex].thingHeight = _g->mouseSlot.thingHeight;
			_g->play.inv.inv[myIndex].name = _g->mouseSlot.name;
			_g->mouseSlot.id = -1;
			_g->mouseSlot.count = -1;
			_g->mouseSlot.thing = "";
			_g->mouseSlot.thingWidth = 0;
			_g->mouseSlot.thingHeight = 0;
			_g->mouseSlot.name = "";
		}
		else if (_g->mouseSlot.count != -1 && _g->play.inv.inv[myIndex].count != -1) //if both have something, swap
		{
			int id = _g->mouseSlot.id;
			int count = _g->mouseSlot.count;
			std::string thing = _g->mouseSlot.thing;
			int thingWidth = _g->mouseSlot.thingWidth;
			int thingHeight = _g->mouseSlot.thingHeight;
			std::string name = _g->mouseSlot.name;
			_g->mouseSlot.id = _g->play.inv.inv[myIndex].id;
			_g->mouseSlot.count = _g->play.inv.inv[myIndex].count;
			_g->mouseSlot.thing = _g->play.inv.inv[myIndex].thing;
			_g->mouseSlot.thingWidth = _g->play.inv.inv[myIndex].thingWidth;
			_g->mouseSlot.thingHeight = _g->play.inv.inv[myIndex].thingHeight;
			_g->mouseSlot.name = _g->play.inv.inv[myIndex].name;
			_g->play.inv.inv[myIndex].id = id;
			_g->play.inv.inv[myIndex].count = count;
			_g->play.inv.inv[myIndex].thing = thing;
			_g->play.inv.inv[myIndex].thingWidth = thingWidth;
			_g->play.inv.inv[myIndex].thingHeight = thingHeight;
			_g->play.inv.inv[myIndex].name = name;
		}
		name = _g->play.inv.inv[myIndex].name; //update the gui object's name
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