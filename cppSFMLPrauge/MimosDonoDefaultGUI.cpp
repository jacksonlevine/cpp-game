#include "mimosdono/MimosDonoDefaultGUI.h"

namespace gui
{
	GUIView mdPauseMenu();

	std::unordered_map<std::string, GUIView> MimosDonoDefaultGUI::getViews()
	{
		std::unordered_map<std::string, GUIView> mdgui;

		//Create GUI Views and add them to map
		//Views must take in a model at some point
		GUIView pause = mdPauseMenu();
		mdgui.insert_or_assign("pause", pause);

		return mdgui;
	}

	GUIView mdPauseMenu()
	{
		GUIView pause;
		GUIContainer container;
		for (int i = 0; i < 4; i++)
		{
			GUIObject obj(100, 50);
			container.objects.push_back(obj);
		}
		container.x = 200;
		container.y = 50;
		container.width = 100;
		container.height = 500;
		pause.containers.push_back(container);
		return pause;
	}
}