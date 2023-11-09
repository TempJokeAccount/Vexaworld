#pragma once
#include "GameObject.h"
#include "Scene.h"
#include "SimpleSDLWrapper.h"

class ImageBox : public GameObject {
  public:
    Image *image;
    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    ImageBox(Scene *scene, float x, float y, int width, int height, std::string path) : GameObject(scene, x, y, width, height), image() {
        image = scene->game->getImage(path);
    };
    ImageBox(Scene *scene, float x, float y, int width, int height, Image *image) : GameObject(scene, x, y, width, height), image(image){};
    ImageBox(Scene *scene, float x, float y, int width, int height, std::string path, double angle, SDL_RendererFlip flip) : GameObject(scene, x, y, width, height), flip(flip), angle(angle) {
        image = scene->game->getImage(path);
    };

    virtual void render() {
        renderer->drawImage(image, x - scene->cameraX, y - scene->cameraY, width, height, angle, flip);
    }
};