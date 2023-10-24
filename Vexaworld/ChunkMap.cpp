#include "ChunkMap.h"
#include "Game.h"
#include <iostream>

ChunkMap::ChunkMap(Game* game): game(game)
{
	create(0, 0);
}

ChunkMap::~ChunkMap()
{
	for (auto& coords : chunks)
	{
		delete coords.second;
	}
}

Chunk* ChunkMap::create(std::pair<long, long> pair)
{
	Chunk* chunk = new Chunk(game, pair.first, pair.second);
	chunks[pair] = chunk;
	if(pair.second == 0) chunk->loadTestChunk();
	return chunk;
}


Chunk* ChunkMap::create(long x, long y)
{
	Chunk* chunk = new Chunk(game, x, y);
	chunks[std::make_pair(x, y)] = chunk;
	chunk->loadTestChunk();
	return chunk;
}

Chunk* ChunkMap::get(long x, long y)
{
	auto pair = std::make_pair(x, y);
	if (!chunks.count(pair))
	{
		return create(pair);
	}
	return chunks[pair];
}

void ChunkMap::render()
{
	for (const auto& p : chunks)
	{
		p.second->render();
	}
}