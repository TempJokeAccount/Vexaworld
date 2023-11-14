#pragma once
#include "Block.h"
#include "GameObject.h"
#include "Scene.h"
#include "defs.h"
#include <array>

struct BlockOptions;

class Chunk final {
  public:
    Scene *scene;
    int x;
    int y;
    Chunk(Scene *scene, float x, float y);
    ~Chunk();
    Block *blocks[CHUNK_SIZE][CHUNK_SIZE];
    void render();
    void loadTestChunk();
    Block *getBlockAtAbsolutePos(float x, float y);
    Block *getBlockIntersecting(float x, float y, int width, int height, SDL_Rect *returnRect);
    Block *placeBlock(BlockOptions options, float x, float y);
    SDL_Rect getBlockRect(int x, int y);
    SDL_Rect getRect();
    void deleteBlock(float x, float y);

  private:
};