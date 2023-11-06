#pragma once
#include "Block.h"
#include "GameObject.h"
#include "Scene.h"
#include "defs.h"
#include <array>

struct BlockOptions;

class Chunk final : public GameObject {
  public:
    Chunk(Scene *scene, float x, float y);
    ~Chunk();
    Block *blocks[CHUNK_SIZE][CHUNK_SIZE];
    virtual void render();
    void loadTestChunk();
    Block *getBlockAtAbsolutePos(float x, float y);
    Block *getBlockIntersecting(float x, float y, int width, int height);
    Block *placeBlock(BlockOptions options, float x, float y);
    void deleteBlock(float x, float y);
};