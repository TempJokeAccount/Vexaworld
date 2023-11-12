#include "Scene.h"
#include "Chunk.h"
#include "ChunkMap.h"
#include "Game.h"
#include "ObjectPlacer.h"
#include "Player.h"
#include "defs.h"
#include "Hotbar.h"
#include <cmath>

Scene::Scene(Game *game, SimpleSDLWrapper *renderer) : game(game), renderer(renderer) {
    hotbar = new Hotbar(this);
    player = new Player(this, 10, 10, PLAYER_WIDTH, PLAYER_HEIGHT, "firtir.png");
    chunks = new ChunkMap(this);
    objectPlacer = new ObjectPlacer(this);
}

Scene::~Scene() {
    delete player;
    delete chunks;
    delete objectPlacer;
}

void Scene::update(const float deltaTime) {
    player->update(deltaTime);
    auto dimensions = renderer->getDimensions();

    cameraX = std::lerp(cameraX, player->x - dimensions.width / 2, 0.01 * deltaTime);
    cameraY = std::lerp(cameraY, player->y - dimensions.height / 2, 0.003 * deltaTime);

    objectPlacer->update();
}

void Scene::render() {
    player->render();
    chunks->render();
    objectPlacer->render();
    hotbar->render();
}

Chunk *Scene::getChunkAtPos(float x, float y) {
    int chunkX = x / CHUNK_SIZE_PIXELS;
    int chunkY = y / CHUNK_SIZE_PIXELS;
    if (x < 0)
        chunkX--;
    if (y < 0)
        chunkY--;
    return chunks->get(chunkX, chunkY);
}

Block *Scene::getBlockAtPos(float x, float y) {
    return getChunkAtPos(x, y)->getBlockAtAbsolutePos(x, y);
}

void Scene::handleEvent(SDL_Event &event) {
    switch (event.type) {
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            bool keyHeld = event.type == SDL_KEYDOWN;
            switch (event.key.keysym.sym) {
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
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT) {
                leftMouseHeld = event.button.state;
            }
            break;
    }
}

void Scene::blur() {
    leftMouseHeld = false;
    player->isJumpHeld = false;
    player->isLeftHeld = false;
    player->isRightHeld = false;
    objectPlacer->deleteMode = false;
}