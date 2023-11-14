#pragma once
#include "Block.h"
#include "GameObject.h"
#include "ImageBox.h"
#include "Scene.h"

class Player final : public ImageEntity {
  public:
    using ImageEntity::ImageEntity;
    float velY = 0;
    float velX = 0;
    bool isGrounded = false;
    bool isLeftHeld = false;
    bool isRightHeld = false;
    bool isJumpHeld = false;
    void update(float deltaTime);
    virtual void render() override;

  private:
    void snapToTop(SDL_Rect rect);
    void snapToBottom(SDL_Rect rect);
    void snapToLeft(SDL_Rect rect);
    void snapToRight(SDL_Rect rect);
    void applyGravity(float deltaTime);
    SDL_Rect getBlockerRect(float x, float y);
};
