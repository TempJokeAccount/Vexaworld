#include "Chunk.h"
#include "Block.h"
#include "GameObject.h"
#include "ObjectPlacer.h"
#include "defs.h"
#include <array>

Chunk::Chunk(Scene *scene, float x, float y) : GameObject(scene, x * CHUNK_SIZE * BLOCK_SIZE, y * CHUNK_SIZE * BLOCK_SIZE, CHUNK_SIZE * BLOCK_SIZE, CHUNK_SIZE * BLOCK_SIZE) {
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
    for (int i = 0; i < CHUNK_SIZE; i++) {
        for (int j = 0; j < CHUNK_SIZE; j++) {
            Block *block = blocks[i][j];
            if (block != nullptr) {
                block->render();
            }
        }
    }
}

void Chunk::loadTestChunk() {
    for (int i = 0; i < CHUNK_SIZE; i++) {
        blocks[i][CHUNK_SIZE - 1] = new Block(this, i, 15);
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

Block *Chunk::getBlockIntersecting(float x, float y, int width, int height) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            Block *block = blocks[i][j];
            if (block != nullptr && block->intersects(x, y, width, height)) {
                return block;
            }
        }
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
    return blocks[accX][accY] = new Block(this, accX, accY);
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