#include "mimosdono/JacksObjects.h"

namespace objs
{
	InventorySlot::InventorySlot()
	{
		thingWidth = 0;
		thingHeight = 0;
		id = -1;
		count = -1;
		thing = "";
		name = "empty";
	};
	Inventory::Inventory()
	{
		for (int i = 0; i < size; i++)
		{
			inv[i].id = -1;
			inv[i].count = -1;
		}
	}
	int Inventory::findItem(int id)
	{
		for (int i = 0; i < size; i++)
		{
			if (inv[i].id == id)
			{
				return i;
			}
		}
		return -1;
	}
	int Inventory::firstOpenSlot()
	{
		for (int i = 0; i < size; i++)
		{
			if (inv[i].id == -1)
			{
				return i;
			}
		}
		return -1;
	}
	std::vector<std::string> Inventory::getInfo()
	{
		std::vector<std::string> i;
		//thing, name, count
		for (InventorySlot slot : inv)
		{
			i.push_back(slot.thing);
			i.push_back(slot.name);
			i.push_back(std::to_string(slot.count));
		}
	}
}