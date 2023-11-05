#pragma once
#include "Game.h"
#include "SDL.h"

enum WindowEvent
{
	MOUSE_MOVE,
	MOUSE_DOWN,
};

class Window 
{
public:
	Window(Game* game);
	virtual ~Window() {};
	bool focus = false;
	int x, y, width, height;
	Game* game;
	void render();
	virtual void update() = 0;
	virtual void renderContent(int x, int y, int width, int height) = 0;
	virtual void handleEvent(WindowEvent event) = 0;
};