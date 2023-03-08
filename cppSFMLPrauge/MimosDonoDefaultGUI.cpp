#include "mimosdono/MimosDonoDefaultGUI.h"

namespace gui
{
	GUIView mdPauseMenu(int scw, int sch);

	std::unordered_map<std::string, GUIView> MimosDonoDefaultGUI::getViews(int screenwidth, int screenheight)
	{
		std::unordered_map<std::string, GUIView> mdgui;

		//Create GUI Views and add them to map
		//Views must take in a model at some point
		GUIView pause = mdPauseMenu(screenwidth, screenheight);
		mdgui.insert_or_assign("pause", pause);

		return mdgui;
	}

	GUIView mdPauseMenu(int scw, int sch)
	{
		GUIView pause;
		GUIContainer container;
		std::string buttons[4] =
		{
			"Settings",
			"Quit Game"
		};

		for (int i = 0; i < 2; i++)
		{
			GUIObject obj(150, 50, buttons[i]);
			container.objects.push_back(obj);
		}
		container.width = 200;
		container.height = 250;
		container.x = (scw/2)-(container.width/2);
		container.y = (sch / 2) - (container.height / 2);
		pause.containers.push_back(container);
		return pause;
	}
}