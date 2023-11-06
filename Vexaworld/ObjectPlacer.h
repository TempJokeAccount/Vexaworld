#pragma once
#include "Block.h"
#include "ImageBox.h"
#include "Scene.h"

struct BlockOptions {
};

class ObjectPlacer : public ImageBox {
  public:
    ObjectPlacer(Scene *scene);
    void update();
    bool deleteMode = false;

  private:
    BlockOptions blockOptions;
};