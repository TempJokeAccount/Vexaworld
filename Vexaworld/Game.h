#pragma once
#include "SimpleSDLWrapper.h"
#include <map>
#include <vector>

class Window;
class Scene;

class Game 
{
public:
	Game(SimpleSDLWrapper* renderer);
	~Game();
	std::vector<Window*> windows{};
	std::map<std::string, Image*> imageCache{};
	void update(float deltaTime);
	void render();
	void handleEvent(SDL_Event& event, bool* quit);
	SimpleSDLWrapper* renderer;
	Scene* scene;
	int mouseX = 0;
	int mouseY = 0;
	bool leftMouseHeld = false;
	// The window that was last clicked. If null, the scene is focused.
	Window* focusedWindow;
};