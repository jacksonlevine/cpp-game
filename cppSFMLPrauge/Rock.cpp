#include "mimosdono/JacksObjects.h"

namespace objs
{
	std::string Rock::makeRock()
	{
		int width = 23;
		int height = 15;
		std::vector<int> xVariations;
		xVariations.push_back(0);
		xVariations.push_back(-1);
		xVariations.push_back(-2);
		xVariations.push_back(0);
		xVariations.push_back(-1);
		xVariations.push_back(-2);
		xVariations.push_back(0);
		xVariations.push_back(-1);
		std::vector<int> yVariations;
		yVariations.push_back(0);
		yVariations.push_back(0);
		yVariations.push_back(0);
		yVariations.push_back(-1);
		yVariations.push_back(-1);
		yVariations.push_back(-1);
		yVariations.push_back(-2);
		yVariations.push_back(-2);
		std::vector<int> lightVariations;
		lightVariations.push_back(2);
		lightVariations.push_back(2);
		lightVariations.push_back(3);
		lightVariations.push_back(2);
		lightVariations.push_back(3);
		lightVariations.push_back(3);
		lightVariations.push_back(2);
		lightVariations.push_back(3);
		std::vector<int> intString;
		for (int i = 0; i < width; i++)
		{
			for (int j = 0; j < height; j++)
			{
				intString.push_back(0);
			}
		}
		int size = (int)(3 + getRandom() * 6);
		float orx = (int)(width / 2 + (getRandom()));
		float ory = (int)(height - 1);
		for (int i = 0; i < size; i++)
		{
			float dist = getRandom() * i;
			float brushX = orx + (dist - (getRandom() * i));
			float brushY = ory - dist;
			for (int j = 0; j < xVariations.size(); j++)
			{
				int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
				if (index > 0 && index < width * height)
				{
					intString[index] = lightVariations[j];
				}
			}
		}
		orx = (int)(width / 3) * 2 - getRandom();
		ory = (int)(height - 1);
		for (int i = 0; i < size; i++)
		{
			float dist = getRandom() * i;
			float brushX = orx + (dist - (getRandom() * i));
			float brushY = ory - dist;
			for (int j = 0; j < xVariations.size(); j++)
			{
				int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
				if (index > 0 && index < width * height)
				{
					intString[index] = lightVariations[j];
				}
			}
		}
		orx = (int)(width / 2.5) + getRandom();
		ory = (int)(height - 1);
		for (int i = 0; i < size; i++)
		{
			float dist = getRandom() * i;
			float brushX = orx + (dist - (getRandom() * i));
			float brushY = ory - dist;
			for (int j = 0; j < xVariations.size(); j++)
			{
				int index = (int)std::floor(brushX + xVariations[j]) + ((int)std::floor(brushY + yVariations[j]) * width);
				if (index > 0 && index < width * height)
				{
					intString[index] = lightVariations[j];
				}
			}
		}
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				if (intString[(j * width) + i] == 0)
				{
					if ((j * width) + i - 1 < width * height && (j * width) + i - 1 > 0)
					{
						if (intString[(j * width) + i - 1] == 2 || intString[(j * width) + i - 1] == 3)
						{
							intString[(j * width) + i] = 1;
						}
					}
					if ((j * width) + i + 1 < width * height && (j * width) + i + 1 > 0)
					{
						if (intString[(j * width) + i + 1] == 2 || intString[(j * width) + i + 1] == 3)
						{
							intString[(j * width) + i] = 1;
						}
					}
					if ((j * width) + i - width < width * height && (j * width) + i - width > 0)
					{
						if (intString[(j * width) + i - width] == 2 || intString[(j * width) + i - width] == 3)
						{
							intString[(j * width) + i] = 1;
						}
					}
					if ((j * width) + i + width < width * height && (j * width) + i + width > 0)
					{
						if (intString[(j * width) + i + width] == 2 || intString[(j * width) + i + width] == 3)
						{
							intString[(j * width) + i] = 1;
						}
					}
					if (j == height - 1)
					{
						if (intString[(j * width) + i] == 2 || intString[(j * width) + i] == 3)
						{
							intString[(j * width) + i] = 1;
						}
					}
				}
			}
		}
		std::string str = "";
		for (int j = 0; j < height; j++)
		{
			for (int i = 0; i < width; i++)
			{
				int index = (j * width) + i;
				if (intString[index] == 0)
				{
					str = str + '0';
				}
				else
					if (intString[index] == 2)
					{
						str = str + 'n';
					}
					else
						if (intString[index] == 3)
						{
							str = str + 's';
						}
						else
							if (intString[index] == 1)
							{
								str = str + 'a';
							}
			}
		}
		return str;
	}
}