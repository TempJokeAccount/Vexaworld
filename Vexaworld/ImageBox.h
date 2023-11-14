#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "SimpleSDLWrapper.h"

class ImageEntity : public Entity {
  public:
    Image *image;
    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    ImageEntity(Scene *scene, float x, float y, int width, int height, std::string path) : Entity(scene, x, y, width, height), image(scene->game->getImage(path)){};
    ImageEntity(Scene *scene, float x, float y, int width, int height, Image *image) : Entity(scene, x, y, width, height), image(image){};
    virtual void render() {
        renderer->drawImage(image, x - scene->cameraX, y - scene->cameraY, width, height, angle, flip);
    }
};