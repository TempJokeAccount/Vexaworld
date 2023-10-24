#pragma once
#include "GameObject.h"
#include "Game.h"
#include "defs.h"
#include <array>
#include "Block.h"

struct BlockOptions;

class Chunk final : public GameObject
{
public:
	Chunk(Game* game, float x, float y);
	~Chunk();
	Block* blocks[CHUNK_SIZE][CHUNK_SIZE];
	virtual void render();
	void loadTestChunk();
	Block* getBlockAtAbsolutePos(float x, float y);
	Block* getBlockIntersecting(float x, float y, int width, int height);
	Block* placeBlock(BlockOptions options, float x, float y);
	void deleteBlock(float x, float y);
};