#pragma once
#include "ImageBox.h"
#include "Game.h"

class Chunk;

class Block final : public ImageBox
{
public:
	Block(Chunk* chunk, int x, int y);
};