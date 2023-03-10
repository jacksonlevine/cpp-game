#include "mimosdono/GUIObjects.h"
#include "mimosdono/Game.h"
#include <iostream>
namespace gui
{
	GUIObject::GUIObject(jl::Game* game, int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
		_g = game;
		mouseOver = false;
	}
	GUIObject::GUIObject(jl::Game* game, int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
		_g = game;
		mouseOver = false;
	}
	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he) : GUIObject(g, wi, he)
	{

	}
	GUIQuitButton::GUIQuitButton(jl::Game* g, int wi, int he, std::string te) : GUIObject(g, wi, he, te)
	{

	}
	void GUIObject::execute()
	{
		std::cout << "I am groot! GUI object";
	}
	jl::Game* GUIView::getGameInstance()
	{
		return _g;
	}
	jl::Game* GUIObject::getGameInstance()
	{
		return _g;
	}
	void GUIQuitButton::execute()
	{
		getGameInstance()->window.close();
	}
}