#include "Window.h"
#include "Game.h"

Window::Window(Game* game) : game(game)
{
	x = 100;
	y = 100;
	width = 100;
	height = 100;
}

void Window::render()
{

	renderContent();
}