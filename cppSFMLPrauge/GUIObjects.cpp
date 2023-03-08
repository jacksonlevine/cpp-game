#include "mimosdono/GUIObjects.h"

namespace gui
{
	GUIObject::GUIObject(int wi, int he)
	{
		width = wi;
		height = he;
		text = "";
	}
	GUIObject::GUIObject(int wi, int he, std::string te)
	{
		width = wi;
		height = he;
		text = te;
	}
}