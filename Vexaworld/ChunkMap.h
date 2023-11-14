#pragma once
#include "Chunk.h"
#include <map>

class ChunkMap {
  public:
    ChunkMap(Scene *scene);
    ~ChunkMap();
    Chunk *get(int x, int y);
    Chunk *create(int x, int y);
    Chunk *create(std::pair<int, int> pair);
    void render();

  private:
    Scene *scene;
    std::map<std::pair<int, int>, Chunk *> chunks;
};