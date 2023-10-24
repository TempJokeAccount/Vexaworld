#pragma once
#include "ImageBox.h"
#include "Game.h"
#include "Block.h"

struct BlockOptions
{

};

class ObjectPlacer : public ImageBox
{
public:
	ObjectPlacer(Game* game);
	void update();
	bool deleteMode = false;
private:
	BlockOptions blockOptions;
};