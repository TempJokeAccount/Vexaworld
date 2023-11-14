#pragma once
#include "Scene.h"
#include "SimpleSDLWrapper.h"

class Entity {
  public:
    Entity(Scene *scene, float x, float y, int width, int height);
    Scene *scene;
    SimpleSDLWrapper *renderer;
    float x;
    float y;
    int width;
    int height;
    SDL_Rect getRect() ;
    virtual bool intersects(SDL_Rect rect);
    virtual bool intersects(float x, float y, int width, int height);
    virtual void render() = 0;
    static bool rectIntersects(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2);
};