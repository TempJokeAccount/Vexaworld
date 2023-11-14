#include "GameObject.h"
#include "Scene.h"

bool Entity::rectIntersects(float x1, float y1, int w1, int h1, float x2, float y2, int w2, int h2) {
    if (x1 >= x2 + w2 || x2 >= x1 + w1 || y1 >= y2 + h2 || y2 >= y1 + h1) {
        return false;
    } else {
        return true;
    }
}

Entity::Entity(Scene *scene, float x, float y, int width, int height) : x(x), y(y), width(width), height(height), scene(scene) {
    renderer = scene->renderer;
}

bool Entity::intersects(SDL_Rect rect) {
    return rectIntersects(x, y, width, height, rect.x, rect.y, rect.w, rect.h);
}

bool Entity::intersects(float x, float y, int width, int height) {
    return rectIntersects(this->x, this->y, this->width, this->height, x, y, width, height);
}

SDL_Rect Entity::getRect() {
    return {int(x), int(y), width, height};
}