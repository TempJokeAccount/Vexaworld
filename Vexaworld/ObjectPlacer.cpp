#include "ObjectPlacer.h"
#include "Block.h"
#include "Chunk.h"
#include "ImageBox.h"
#include "defs.h"
#include "scene.h"

ObjectPlacer::ObjectPlacer(Scene *scene) : ImageBox(scene, 0, 0, BLOCK_SIZE, BLOCK_SIZE, "block.png") {
    blockOptions = {};
    image->setAlpha(127);
}

void ObjectPlacer::update() {
    Game *game = scene->game;
    x = game->mouseX + scene->cameraX;
    y = game->mouseY + scene->cameraY;
    if (x < 0)
        x -= BLOCK_SIZE;
    if (y < 0)
        y -= BLOCK_SIZE;
    x = (int)x / BLOCK_SIZE * BLOCK_SIZE;
    y = (int)y / BLOCK_SIZE * BLOCK_SIZE;

    if (scene->leftMouseHeld) {
        Chunk *chunk = scene->getChunkAtPos(x + 1, y + 1);
        if (deleteMode) {
            chunk->deleteBlock(x, y);
        } else {
            chunk->placeBlock({}, x, y);
        }
    }
}