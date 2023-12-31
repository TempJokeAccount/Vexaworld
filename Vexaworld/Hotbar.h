#pragma once
#include "Scene.h"
#include "Block.h"
#include "ObjectPlacer.h"

class Hotbar {
  public:
    Hotbar(Scene *scene);
    std::vector<BlockOptions> blocks;
    int selectedBlockIndex = 0;
    int x;
    int y;
    Scene *scene;
    void render();
    void onClick(SDL_Point mouse);
};