#pragma once
#include "Game.h"
#include "SimpleSDLWrapper.h"

class GameObject
{
public:
    GameObject(Game* game, float x, float y, int width, int height);
    Game* game;
    SimpleSDLWrapper* renderer;
    float x;
    float y;
    int width;
    int height;
    virtual bool intersects(GameObject* gameObject);
    virtual bool intersects(float x, float y, int width, int height);
    virtual void render() = 0;
    static bool rectIntersects(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);
};