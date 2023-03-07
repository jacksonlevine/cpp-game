#pragma once
#include "GUIController.h"
#include <unordered_map>
#include <string>

namespace gui
{
	class MimosDonoDefaultGUI
	{
	public:
		static std::unordered_map<std::string, GUIView> getViews();
	};
}