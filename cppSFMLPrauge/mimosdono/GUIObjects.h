#pragma once
#include "JacksObjects.h"
#include <vector>
#include "Game.h"

namespace gui
{
	class GUIObject
	{
	private:
		jl::Game* _g;
	public:
		int width;
		int height;
		int x;
		int y;
		std::string text;
		bool mouseOver;
		GUIObject(jl::Game* _g, int wi, int he);
		GUIObject(jl::Game* _g, int wi, int he, std::string te);
		virtual void execute();
		jl::Game* getGameInstance();
	};

	class GUIQuitButton : public GUIObject
	{
	public:
		GUIQuitButton(jl::Game* g, int wi, int he);
		GUIQuitButton(jl::Game* g, int wi, int he, std::string te);
		void execute();
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
	private:
		jl::Game* _g;
	public:
		jl::Game* getGameInstance();
		std::vector<GUIContainer> containers;
	};
}