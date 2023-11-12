#pragma once
#include "Scene.h"
#include "Block.h"
#include "ObjectPlacer.h"

class Hotbar {
    Hotbar(Scene *scene);
    std::vector<BlockOptions> blocks;
    Scene *scene;
    void render();
};