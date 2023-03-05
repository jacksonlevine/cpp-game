#include "mimosdono/JacksObjects.h"

namespace objs
{
	InventorySlot::InventorySlot()
	{
		thingWidth = 3;
		thingHeight = 3;
		id = -1;
		count = -1;
		thing = "0a0ata0a0";
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
}