#include "mimosdono/Game.h"
int main() 
{ 
	sf::Event e;
	jl::Game g;
	while (g.window.isOpen())
	{
		while (g.window.pollEvent(e))
		{
			g.pollEvents(e);
		}
		g.draw();
	}
	return 0; 
}