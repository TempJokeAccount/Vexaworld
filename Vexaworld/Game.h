#pragma once
#include "SimpleSDLWrapper.h"
#include <map>

class Player;
class ChunkMap;
class Chunk;
class Block;
class GameObject;
class ObjectPlacer;

class Game 
{
public:
	Game(SimpleSDLWrapper* renderer);
	~Game();
	int cameraX = 0;
	int cameraY = 0;
	std::map<std::string, Image*>* imageCache;
	void update(float deltaTime);
	void render(float deltaTime);
	void handleEvent(SDL_Event &event, bool *quit);
	SimpleSDLWrapper* renderer;
	Chunk* getChunkAtPos(float x, float y);
	Block* getBlockAtPos(float x, float y);
	Player* player;
	int mouseX = 0;
	int mouseY = 0;
	bool leftMouseHeld = false;
private:
	ChunkMap* chunks;
	ObjectPlacer* objectPlacer;
};