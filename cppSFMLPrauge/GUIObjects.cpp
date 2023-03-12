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
	}
	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		mouseOver = false;
	}
	GUICloseButton::GUICloseButton(jl::Game* g, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string ro)
	{
		width = wi;
		height = he;
		text = "";
		_g = g;
		mouseOver = false;
		route = ro;
	}
	GUIRouteButton::GUIRouteButton(jl::Game* g, int wi, int he, std::string te, std::string ro)
	{
		width = wi;
		height = he;
		text = te;
		_g = g;
		mouseOver = false;
		route = ro;
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