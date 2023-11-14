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
    SDL_Rect xBlocker = getBlockerRect(newX, y);
    SDL_Rect yBlocker = getBlockerRect(x, newY);
    isGrounded = false;

    if (xBlocker.x == -1) {
        x = newX;
    } else {
        if (xBlocker.x > this->x + (float)PLAYER_WIDTH / 2) {
            snapToLeft(xBlocker);
        } else {
            snapToRight(xBlocker);
        }
    }

    if (yBlocker.x == -1) {
        y = newY;
    } else {
        if (yBlocker.y > this->y - (float)PLAYER_HEIGHT / 2) {
            isGrounded = true;
            snapToBottom(yBlocker);
        } else {
            snapToTop(yBlocker);
        }
        velY = 0;
    }
}

void Player::snapToTop(SDL_Rect rect) {
    y = rect.y + BLOCK_SIZE;
}

void Player::snapToBottom(SDL_Rect rect) {
    y = rect.y - PLAYER_HEIGHT;
}

void Player::snapToLeft(SDL_Rect rect) {
    x = rect.x - PLAYER_WIDTH;
}

void Player::snapToRight(SDL_Rect rect) {
    x = rect.x + BLOCK_SIZE;
}

SDL_Rect Player::getBlockerRect(float x, float y) {
    SDL_Rect rect;
    scene->getChunkAtPos(x, y)->getBlockIntersecting(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, &rect);
    return rect;
}

void Player::render() {
    float accX = x;
    float accY = y;
    accX -= float(width) / 2;
    accY -= height;
    accX -= scene->cameraX;
    accY -= scene->cameraY;
    renderer->drawImage(image, accX, accY, width * 2, height * 2, 0, flip);
}