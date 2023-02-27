#include "Game.h"
int main() 
{ 
	sf::Event e;
	jl::Game g;
	while (window.isOpen())
	{
		while (window.pollEvent(e))
		{
			g.pollEvents(e);
		}
		g.draw();
	}
	return 0; 
}