#include "Scene.h"
#include "Game.h"
#include "defs.h"
#include "Player.h"
#include "Chunk.h"
#include "ObjectPlacer.h"
#include "ChunkMap.h"
#include <cmath>


Scene::Scene(Game* game, SimpleSDLWrapper* renderer) : game(game), renderer(renderer)
{
	player = new Player(this, 10, 10, PLAYER_WIDTH, PLAYER_HEIGHT, "firtir.png");
	chunks = new ChunkMap(this);
	objectPlacer = new ObjectPlacer(this);
}

Scene::~Scene()
{
	delete player;
	delete chunks;
	delete objectPlacer;
}

void Scene::update(const float deltaTime)
{
	player->update(deltaTime);
	auto dimentions = renderer->getDimentions();

	cameraX = std::lerp(cameraX, player->x - dimentions.width / 2, 0.01 * deltaTime);
	cameraY = std::lerp(cameraY, player->y - dimentions.height / 2, 0.003 * deltaTime);

	objectPlacer->update();
}

void Scene::render()
{
	player->render();
	chunks->render();
	objectPlacer->render();
}

Chunk* Scene::getChunkAtPos(float x, float y)
{
	int chunkX = x / CHUNK_SIZE_PIXELS;
	int chunkY = y / CHUNK_SIZE_PIXELS;
	if (x < 0) chunkX--;
	if (y < 0) chunkY--;
	return chunks->get(chunkX, chunkY);
}

Block* Scene::getBlockAtPos(float x, float y)
{
	return getChunkAtPos(x, y)->getBlockAtAbsolutePos(x, y);
}