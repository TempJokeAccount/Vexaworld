#pragma once
#include "Game.h"
#include "GameObject.h"
#include "Block.h"
#include "ImageBox.h"

class Player final : public ImageBox
{
	friend Game;
public:
	using ImageBox::ImageBox;
	float velY = 0;
	float velX = 0;
	bool isGrounded = false;
	void update(float deltaTime);
private:
	bool isLeftHeld = false;
	bool isRightHeld = false;
	bool isJumpHeld = false;
	void snapToTop(Block* block);
	void snapToBottom(Block* block);
	void snapToLeft(Block* block);
	void snapToRight(Block* block);
	void applyGravity(float deltaTime);
	virtual void render() override;
	Block* getBlocker(float x, float y);
};
