#pragma once
#include "Block.h"
#include "GameObject.h"
#include "ImageBox.h"
#include "Scene.h"

class Player final : public ImageBox {
  public:
    using ImageBox::ImageBox;
    float velY = 0;
    float velX = 0;
    bool isGrounded = false;
    bool isLeftHeld = false;
    bool isRightHeld = false;
    bool isJumpHeld = false;
    void update(float deltaTime);
    virtual void render() override;

  private:
    void snapToTop(Block *block);
    void snapToBottom(Block *block);
    void snapToLeft(Block *block);
    void snapToRight(Block *block);
    void applyGravity(float deltaTime);
    Block *getBlocker(float x, float y);
};
