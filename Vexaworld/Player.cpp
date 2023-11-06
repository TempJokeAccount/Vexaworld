#include "Player.h"
#include "Chunk.h"
#include "defs.h"

void Player::update(float deltaTime) {
    velX = 0;
    if (isLeftHeld) {
        velX += -0.4f;
        flip = SDL_FLIP_HORIZONTAL;
    }
    if (isRightHeld) {
        velX += 0.4f;
        flip = SDL_FLIP_NONE;
    }
    if (isJumpHeld && isGrounded) {
        velY = -0.8;
    }
    applyGravity(deltaTime);
}

void Player::applyGravity(float deltaTime) {
    if (!isGrounded) {
        velY = std::min(velY + 0.002f * deltaTime, 2.0f);
    }
    float newX = x + velX * deltaTime;
    float newY = y + velY * deltaTime;
    Block *xBlocker = getBlocker(newX, y);
    Block *yBlocker = getBlocker(x, newY);
    isGrounded = false;

    if (xBlocker == nullptr) {
        x = newX;
    } else {
        if (xBlocker->x > this->x + (float)PLAYER_WIDTH / 2) {
            snapToLeft(xBlocker);
        } else {
            snapToRight(xBlocker);
        }
    }

    if (yBlocker == nullptr) {
        y = newY;
    } else {
        if (yBlocker->y > this->y - (float)PLAYER_HEIGHT / 2) {
            isGrounded = true;
            snapToBottom(yBlocker);
        } else {
            snapToTop(yBlocker);
        }
        velY = 0;
    }
}

void Player::snapToTop(Block *block) {
    y = block->y + BLOCK_SIZE;
}

void Player::snapToBottom(Block *block) {
    y = block->y - PLAYER_HEIGHT;
}

void Player::snapToLeft(Block *block) {
    x = block->x - PLAYER_WIDTH;
}

void Player::snapToRight(Block *block) {
    x = block->x + BLOCK_SIZE;
}

Block *Player::getBlocker(float x, float y) {
    return scene->getChunkAtPos(x, y)->getBlockIntersecting(x, y, PLAYER_WIDTH, PLAYER_HEIGHT);
}

void Player::render() {
    float accX = x;
    float accY = y;
    accX -= (float)width / 2;
    accY -= height;
    accX -= scene->cameraX;
    accY -= scene->cameraY;
    renderer->drawImage(image, accX, accY, width * 2, height * 2, 0, flip);
}