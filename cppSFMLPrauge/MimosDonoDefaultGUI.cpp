#include "mimosdono/MimosDonoDefaultGUI.h"

namespace gui
{
	GUIView mdPauseMenu(jl::Game* g, int scw, int sch);

	std::unordered_map<std::string, GUIView> MimosDonoDefaultGUI::getViews(jl::Game* g, int screenwidth, int screenheight)
	{
		std::unordered_map<std::string, GUIView> mdgui;

		//Create GUI Views and add them to map
		//Views must take in a model at some point
		GUIView pause = mdPauseMenu(g, screenwidth, screenheight);
		mdgui.insert_or_assign("pause", pause);

		return mdgui;
	}

	GUIView mdPauseMenu(jl::Game* g, int scw, int sch)
	{
		GUIView pause;
		GUIContainer container;

		GUIObject obj(g, 150, 50, "Settings");
	
		container.objects.push_back(obj);

		GUIQuitButton quitobj(g, 150, 50, "Quit Game");
		container.objects.push_back(quitobj);

		container.width = 200;
		container.height = 250;
		container.x = (scw/2)-(container.width/2);
		container.y = (sch / 2) - (container.height / 2);
		pause.containers.push_back(container);
		return pause;
	}
}