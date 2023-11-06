#include "Game.h"
#include "SimpleSDLWrapper.h"
#include "defs.h"
#include "TestWindow.h"
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "ObjectPlacer.h"
#include <map>
#include <iostream>

Game::Game(SimpleSDLWrapper* myRenderer) : renderer(myRenderer) 
{
    imageCache = new std::map<std::string, Image*>;
    scene = new Scene(this, myRenderer);
    windows.push_back(new TestWindow(this));
}

Game::~Game()
{
    delete scene;
	delete renderer;
}

void Game::update(const float deltaTime) 
{
    scene->update(deltaTime);
}

void Game::handleEvent(SDL_Event &event, bool *quit)
{
    if (event.type == SDL_QUIT)
    {
        *quit = 1;
        return;
    }

    // mouse
    {
        int x;
        int y;
        uint32_t mouseState = SDL_GetMouseState(&x, &y);
        mouseX = x;
        mouseY = y;
        leftMouseHeld = mouseState & 1;
    }

    for (auto& window : windows)
    {
        if (GameObject::rectIntersects(mouseX, mouseY, 1, 1, window->x, window->y, window->width, window->height))
        {
            window->handleEvent(event);
            return;
        }
    }

    scene->handleEvent(event);
}

void Game::render() 
{
	renderer->setColor(0x1F, 0x1F, 0x1F, 0xFF);
	renderer->clear();

    scene->render();

    for (auto& window : windows)
    {
        window->render();
    }

	renderer->present();
}