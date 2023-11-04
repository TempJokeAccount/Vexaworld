#include "Game.h"
#include "SimpleSDLWrapper.h"
#include "Player.h"	
#include "defs.h"
#include "ChunkMap.h"
#include "ObjectPlacer.h"
#include "TestWindow.h"
#include "Block.h"
#include <map>
#include <cmath>
#include <iostream>

Game::Game(SimpleSDLWrapper* myRenderer) : renderer(myRenderer) 
{
    imageCache = new std::map<std::string, Image*>;
	player = new Player(this, 10, 10, PLAYER_WIDTH, PLAYER_HEIGHT, "firtir.png");
	chunks = new ChunkMap(this);
    objectPlacer = new ObjectPlacer(this);
    windows.push_back(new TestWindow(this));
}

Game::~Game()
{
	delete chunks;
	delete player;
	delete renderer;
}

void Game::update(const float deltaTime) 
{
	player->update(deltaTime);
    auto dimentions = renderer->getDimentions();

    cameraX = std::lerp(cameraX, player->x - dimentions.width / 2, 0.01 * deltaTime);
    cameraY = std::lerp(cameraY, player->y - dimentions.height / 2, 0.003 * deltaTime);

    objectPlacer->update();
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
        if (Block::rectIntersects(mouseX, mouseY, 1, 1, window->x, window->y, window->width, window->height))
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
                    player->isJumpHeld = keyHeld;
                    break;
                case SDLK_a:
                    player->isLeftHeld = keyHeld;
                    break;
                case SDLK_d:
                    player->isRightHeld = keyHeld;
                    break;
                case SDLK_LCTRL:
                    objectPlacer->deleteMode = keyHeld;
                    break;
            }
            break;
        }
    }
}

void Game::render(const float deltaTime) 
{
	renderer->setColor(0x1F, 0x1F, 0x1F, 0xFF);
	renderer->clear();

	player->render();
	chunks->render();
    objectPlacer->render();

    for (auto& window : windows)
    {
        window->render();
    }


	renderer->present();
}

Chunk* Game::getChunkAtPos(float x, float y)
{
    int chunkX = x / CHUNK_SIZE_PIXELS;
    int chunkY = y / CHUNK_SIZE_PIXELS;
    if (x < 0) chunkX--;
    if (y < 0) chunkY--;
	return chunks->get(chunkX, chunkY);
}

Block* Game::getBlockAtPos(float x, float y)
{
	return getChunkAtPos(x, y)->getBlockAtAbsolutePos(x, y);
}