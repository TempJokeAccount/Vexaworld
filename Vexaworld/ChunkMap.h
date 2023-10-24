#pragma once
#include <map>
#include "Chunk.h"
#include "Game.h"

class ChunkMap final {
public:
	ChunkMap(Game* game);
	~ChunkMap();
	Chunk* get(long x, long y);
	Chunk* create(long x, long y);
	Chunk* create(std::pair<long, long> pair);
	void render();
private:
	Game* game;
	std::map<std::pair<long, long>, Chunk*> chunks;
};