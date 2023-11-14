#include "Chunk.h"
#include "Block.h"
#include "GameObject.h"
#include "ObjectPlacer.h"
#include "defs.h"
#include <array>

Chunk::Chunk(Scene *scene, float x, float y) : scene(scene), x(x * CHUNK_SIZE_PIXELS), y(y * CHUNK_SIZE_PIXELS) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            blocks[i][j] = nullptr;
        }
    }
}

Chunk::~Chunk() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            Block *block = blocks[i][j];
            if (block != nullptr) {
                delete block;
            }
        }
    }
}

void Chunk::render() {
    SimpleSDLWrapper *renderer = scene->renderer;
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            Block *block = blocks[i][j];
            if (block != nullptr) {
                renderer->drawImage(block->image, x + i * BLOCK_SIZE - scene->cameraX, y + j * BLOCK_SIZE - scene->cameraY, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }
}

void Chunk::loadTestChunk() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i][CHUNK_SIZE - 1] = new Block{scene->game->getImage("block.png")};
    }
}

Block *Chunk::getBlockAtAbsolutePos(float x, float y) {
    x -= this->x;
    x /= BLOCK_SIZE;
    y -= this->y;
    y /= BLOCK_SIZE;
    if (x < 0 || y < 0) {
        return nullptr;
    }
    if (x > BLOCK_SIZE * CHUNK_SIZE || y > BLOCK_SIZE * CHUNK_SIZE) {
        return nullptr;
    }
    return blocks[(int)x][(int)y];
}

Block *Chunk::getBlockIntersecting(float x, float y, int width, int height, SDL_Rect *returnRect) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            Block *block = blocks[i][j];
            SDL_Rect rect = getBlockRect(i, j);
            if (block != nullptr && Entity::rectIntersects(this->x + rect.x, this->y + rect.y, rect.w, rect.h, x, y, width, height)) {
                if (returnRect) {
                    *returnRect = rect;
                }
                return block;
            }
        }
    }
    if (returnRect) {
        *returnRect = {-1};
    }
    return nullptr;
}

Block *Chunk::placeBlock(BlockOptions options, float x, float y) {
    Block *block = getBlockAtAbsolutePos(x, y);
    if (block != nullptr) {
        return nullptr;
    }
    int accX = x - this->x;
    int accY = y - this->y;
    accX /= BLOCK_SIZE;
    accY /= BLOCK_SIZE;
    return blocks[accX][accY] = new Block{options.image};
}

SDL_Rect Chunk::getBlockRect(int x, int y) {
    return {
        .x = x * BLOCK_SIZE,
        .y = y * BLOCK_SIZE,
        .w = BLOCK_SIZE,
        .h = BLOCK_SIZE,
    };
}

SDL_Rect Chunk::getRect() {
    return {
        .x = x,
        .y = y,
        .w = CHUNK_SIZE_PIXELS,
        .h = CHUNK_SIZE_PIXELS,
    };
}

void Chunk::deleteBlock(float x, float y) {
    Block *block = getBlockAtAbsolutePos(x, y);
    if (block == nullptr) {
        return;
    }
    int accX = x - this->x;
    int accY = y - this->y;
    accX /= BLOCK_SIZE;
    accY /= BLOCK_SIZE;
    delete block;
    blocks[accX][accY] = nullptr;
}