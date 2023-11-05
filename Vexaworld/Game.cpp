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

    // TODO: split game up into scene and game so scene can handle own events

    for (auto& window : windows)
    {
        if (GameObject::rectIntersects(mouseX, mouseY, 1, 1, window->x, window->y, window->width, window->height))
        {
            WindowEvent windowEvent = WindowEvent(2);
            switch (event.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                windowEvent = MOUSE_DOWN;
                break;
            case SDL_MOUSEMOTION:
                windowEvent = MOUSE_MOVE;
                break;
            }
            window->handleEvent(windowEvent);
            return;
        }
    }

    switch (event.type)
    {
        case SDL_KEYDOWN:
        case SDL_KEYUP:
        {
            bool keyHeld = event.type == SDL_KEYDOWN;
                switch (event.key.keysym.sym)
                {
                case SDLK_SPACE:
                    scene->player->isJumpHeld = keyHeld;
                    break;
                case SDLK_a:
                    scene->player->isLeftHeld = keyHeld;
                    break;
                case SDLK_d:
                    scene->player->isRightHeld = keyHeld;
                    break;
                case SDLK_LCTRL:
                    scene->objectPlacer->deleteMode = keyHeld;
                    break;
            }
            break;
        }
    }
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