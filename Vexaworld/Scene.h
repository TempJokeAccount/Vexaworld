#pragma once
#include "Game.h"
#include "SimpleSDLWrapper.h"

class Player;
class ChunkMap;
class ObjectPlacer;
class Block;
class Chunk;

class Scene
{
	friend Game;
public:
	Scene(Game* game, SimpleSDLWrapper* renderer);
	~Scene();

	Game* game;
	SimpleSDLWrapper* renderer;

	int cameraX = 0;
	int cameraY = 0;
	Player* player;

	void update(float deltaTime);
	void render();
	void handleEvent(SDL_Event& event);
	void blur();
	Chunk* getChunkAtPos(float x, float y);
	Block* getBlockAtPos(float x, float y);
private:
	ChunkMap* chunks;
	ObjectPlacer* objectPlacer;
};