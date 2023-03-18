#include "mimosdono/MimosDonoDefaultGUI.h"

namespace gui
{
	GUIView mdPauseMenu(jl::Game* g, int scw, int sch);
	GUIView mdSettingsMenu(jl::Game* g, int scw, int sch);
	GUIView mdInventoryView(jl::Game* g, int scw, int sch);

	std::unordered_map<std::string, GUIView> MimosDonoDefaultGUI::getViews(jl::Game* g, int screenwidth, int screenheight)
	{
		std::unordered_map<std::string, GUIView> mdgui;

		//Create GUI Views and add them to map
		//Views must take in a model at some point
		GUIView pause = mdPauseMenu(g, screenwidth, screenheight);
		mdgui.insert_or_assign("pause", pause);
		GUIView settings = mdSettingsMenu(g, screenwidth, screenheight);
		mdgui.insert_or_assign("settings", settings);
		GUIView inventory = mdInventoryView(g, screenwidth, screenheight);
		mdgui.insert_or_assign("inventory", inventory);

		return mdgui;
	}

	GUIView mdPauseMenu(jl::Game* g, int scw, int sch)
	{
		GUIView view(g);
		int cw = 200; // size of the pause menu container
		int ch = 250;
		GUIContainer container((scw / 2) - (cw / 2), (sch / 2) - (ch / 2), cw, ch);

		GUICloseButton closeobj(g, 150, 50, "Close");
		container.objects.push_back(std::shared_ptr<GUIObject>(new GUICloseButton(closeobj)));

		GUIRouteButton obj(g, 150, 50, "Settings", "settings");
		container.objects.push_back(std::shared_ptr<GUIObject>(new GUIRouteButton(obj)));

		GUIQuitButton quitobj(g, 150, 50, "Quit Game");
		container.objects.push_back(std::shared_ptr<GUIObject>(new GUIQuitButton(quitobj)));

		container.width = 200;
		container.height = 250;
		container.x = (scw/2)-(container.width/2);
		container.y = (sch / 2) - (container.height / 2);
		view.containers.push_back(container);
		return view;
	}

	GUIView mdSettingsMenu(jl::Game* g, int scw, int sch)
	{
		GUIView view(g);
		int cw = 400; // size of the settings menu container
		int ch = 300;
		GUIContainer container((scw / 2) - (cw / 2), (sch / 2) - (ch / 2), cw, ch);

		GUIRouteButton obj(g, 150, 50, "Back", "pause");

		container.objects.push_back(std::shared_ptr<GUIObject>(new GUIRouteButton(obj)));

		view.containers.push_back(container);
		return view;
	}

	GUIView mdInventoryView(jl::Game* g, int scw, int sch)
	{
		GUIView view(g);
		int cw = 700; // size of the inventory container
		int ch = 310;
		GUIContainer container((scw / 2) - (cw / 2), (sch / 2) - (ch / 2), cw, ch);
		int index = 0;
		for (objs::InventorySlot slot : g->play.inv.inv)
		{
			container.objects.push_back(std::shared_ptr<GUIObject>(new GUIInventorySlot(g, 50, 50, index)));
			++index;
		}
		view.containers.push_back(container);
		return view;
	}
}