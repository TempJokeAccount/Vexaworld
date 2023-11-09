#include "Block.h"
#include "Chunk.h"
#include "defs.h"

Block::Block(Chunk *chunk, int chunkX, int chunkY, Image *image) : ImageBox(
                                                                       chunk->scene,
                                                                       chunk->x + chunkX * BLOCK_SIZE,
                                                                       chunk->y + chunkY * BLOCK_SIZE,
                                                                       BLOCK_SIZE,
                                                                       BLOCK_SIZE,
                                                                       image) {
    // ooooooooooooooo
}
Block::Block(Chunk *chunk, int chunkX, int chunkY) : Block(chunk, chunkX, chunkY, chunk->scene->game->getImage("block.png")) {
    // ooooooooooooooo
}