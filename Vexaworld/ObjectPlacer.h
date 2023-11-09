#pragma once
#include "Block.h"
#include "ImageBox.h"
#include "Scene.h"

struct BlockOptions {
    Image *image;
};

class ObjectPlacer final : public ImageBox {
  public:
    ObjectPlacer(Scene *scene);
    void update();
    bool deleteMode = false;
    void render() override;

  private:
    BlockOptions blockOptions;
};