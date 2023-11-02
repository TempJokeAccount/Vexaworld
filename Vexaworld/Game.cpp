#include "Game.h"
#include "SimpleSDLWrapper.h"
#include "Player.h"	
#include "defs.h"
#include "ChunkMap.h"
#include "ObjectPlacer.h"
#include <map>
#include <cmath>

Game::Game(SimpleSDLWrapper* myRenderer) : renderer(myRenderer) 
{
    imageCache = new std::map<std::string, Image*>;
	player = new Player(this, 10, 10, PLAYER_WIDTH, PLAYER_HEIGHT, "firtir.png");
	chunks = new ChunkMap(this);
    objectPlacer = new ObjectPlacer(this);
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
    cameraX = player->x - dimentions.width / 2;
    cameraY = player->y - dimentions.height / 2;
    objectPlacer->update();
}

void Game::handleEvent(SDL_Event &event, bool *quit)
{
    switch (event.type)
    {
        case SDL_QUIT:
            *quit = 1;
            break;
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

    // mouse
    {
        int x;
        int y;
        uint32_t mouseState = SDL_GetMouseState(&x, &y);
        mouseX = x;
        mouseY = y;
        leftMouseHeld = mouseState & 1;
    }
}

void Game::render(const float deltaTime) 
{
	renderer->setColor(0x1F, 0x1F, 0x1F, 0xFF);
	renderer->clear();

	player->render();
	chunks->render();
    objectPlacer->render();

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