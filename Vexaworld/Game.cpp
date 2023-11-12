#include "Game.h"
#include "GameObject.h"
#include "ObjectPlacer.h"
#include "PixelDrawer.h"
#include "Player.h"
#include "Scene.h"
#include "SimpleSDLWrapper.h"

#include "defs.h"
#include <iostream>
#include <map>

Game::Game(SimpleSDLWrapper *myRenderer) : renderer(myRenderer) {
    scene = new Scene(this, myRenderer);
    windows.push_back(new PixelDrawer(this));
}

Game::~Game() {
    delete scene;
    delete renderer;
}

void Game::update(const float deltaTime) {
    scene->update(deltaTime);
}

void Game::handleEvent(SDL_Event &event, bool *quit) {
    if (event.type == SDL_QUIT) {
        *quit = 1;
        return;
    }

    // mouse
    {
        uint32_t mouseState = SDL_GetMouseState(&mouseX, &mouseY);
        leftMouseHeld = mouseState & 1;
    }

    // handle focus
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        focusedWindow = nullptr;
        for (auto &window : windows) {
            if (GameObject::rectIntersects(mouseX, mouseY, 1, 1, window->x, window->y, window->width, window->height)) {
                scene->blur();
                focusedWindow = window;
                break;
            }
        }
    }

    if (focusedWindow) {
        focusedWindow->handleEvent(event);
    } else {
        scene->handleEvent(event);
    }
}

void Game::render() {
    renderer->setColor(0x1F, 0x1F, 0x1F, 0xFF);
    renderer->clear();

    scene->render();

    for (auto &window : windows) {
        window->render();
    }

    renderer->present();
}