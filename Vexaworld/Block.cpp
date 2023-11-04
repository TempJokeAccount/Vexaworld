#include "Block.h"
#include "defs.h"
#include "Chunk.h"

Block::Block(Chunk* chunk, int chunkX, int chunkY) :
	ImageBox(
		chunk->game,
		chunk->x + chunkX * BLOCK_SIZE,
		chunk->y + chunkY * BLOCK_SIZE,
		BLOCK_SIZE,
		BLOCK_SIZE,
		"block.png")
{
	// ooooooooooooooo
}