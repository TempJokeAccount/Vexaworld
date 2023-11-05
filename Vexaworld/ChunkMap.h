#pragma once
#include <map>
#include "Chunk.h"

class ChunkMap final {
public:
	ChunkMap(Scene* scene);
	~ChunkMap();
	Chunk* get(long x, long y);
	Chunk* create(long x, long y);
	Chunk* create(std::pair<long, long> pair);
	void render();
private:
	Scene* scene;
	std::map<std::pair<long, long>, Chunk*> chunks;
};