#pragma once
#include "Game.h"
#include "ImageBox.h"

class Chunk;

class Block final : public ImageBox {
  public:
    Block(Chunk *chunk, int x, int y);
};