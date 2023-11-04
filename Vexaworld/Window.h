#pragma once
#include "Game.h"
#include "SDL.h"
#include <variant>

enum MouseButton 
{
	LEFT_MOUSE_BUTTON, 
	MIDDLE_MOUSE_BUTTON, 
	RIGHT_MOUSE_BUTTON,
};

struct MouseMoveEvent 
{
	int x, y;
};

struct MouseClickEvent 
{
	MouseButton button;
};

typedef std::variant<MouseClickEvent, MouseMoveEvent> WindowEvent;

class Window 
{
public:
	Window(Game* game);
	virtual ~Window();
	bool focus = false;
	int x, y, width, height;
	Game* game;
	void render();
	virtual void renderContent() = 0;
	virtual void handleEvent(WindowEvent event) = 0;
};