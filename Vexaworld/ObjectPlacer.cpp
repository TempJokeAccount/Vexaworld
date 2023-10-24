#include "ObjectPlacer.h"
#include "ImageBox.h"
#include "Game.h"
#include "defs.h"
#include "Block.h"
#include "Chunk.h"

ObjectPlacer::ObjectPlacer(Game* game) : ImageBox(game, 0, 0, BLOCK_SIZE, BLOCK_SIZE, "block.png")
{
	blockOptions = {};
	image->setAlpha(127);
}

void ObjectPlacer::update()
{
	x = game->mouseX + game->cameraX;
	y = game->mouseY + game->cameraY;
	if (x < 0) x -= BLOCK_SIZE;
	if (y < 0) y -= BLOCK_SIZE;
	x = (int)x / BLOCK_SIZE * BLOCK_SIZE;
	y = (int)y / BLOCK_SIZE * BLOCK_SIZE;

	if (game->leftMouseHeld)
	{
		Chunk* chunk = game->getChunkAtPos(x + 1, y + 1);
		if (deleteMode)
		{
			chunk->deleteBlock(x, y);
		}
		else
		{
			chunk->placeBlock({}, x, y);
		}
	}
}