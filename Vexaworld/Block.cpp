#include "Block.h"
#include "Chunk.h"
#include "defs.h"

Block::Block(Chunk *chunk, int chunkX, int chunkY) : ImageBox(
                                                         chunk->scene,
                                                         chunk->x + chunkX * BLOCK_SIZE,
                                                         chunk->y + chunkY * BLOCK_SIZE,
                                                         BLOCK_SIZE,
                                                         BLOCK_SIZE,
                                                         "block.png") {
    // ooooooooooooooo
}