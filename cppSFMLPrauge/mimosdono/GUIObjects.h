#pragma once
#include "JacksObjects.h"
#include <vector>
#include "Game.h"

namespace gui
{
	class GUIObject
	{

	public:
		jl::Game* _g;
		int width;
		int height;
		int x;
		int y;
		std::string text;
		bool mouseOver;
		virtual void execute() = 0;
	};

	class GUIQuitButton : public GUIObject
	{
	public:
		GUIQuitButton(jl::Game* g, int wi, int he);
		GUIQuitButton(jl::Game* g, int wi, int he, std::string te);
		virtual void execute();
	};

	class GUIRouteButton : public GUIObject
	{
	public:
		std::string route;
		GUIRouteButton(jl::Game* g, int wi, int he, std::string ro);
		GUIRouteButton(jl::Game* g, int wi, int he, std::string te, std::string ro);
		virtual void execute();
	};

	class GUICloseButton : public GUIObject
	{
	public:
			GUICloseButton(jl::Game* g, int wi, int he);
			GUICloseButton(jl::Game* g, int wi, int he, std::string te);
			virtual void execute();
	};

	class GUIContainer
	{
	public:
		int x;
		int y;
		int width;
		int height;
		std::vector<std::shared_ptr<GUIObject>> objects;
		GUIContainer();
		GUIContainer(int i, int j, int wi, int he);
	};

	class GUIView
	{
	public:
		jl::Game* _g;
		//std::optional<BASE CLASS INTERFACE!!!&> Model;
		GUIView();
		GUIView(jl::Game* g);
		std::vector<GUIContainer> containers;
	};
}