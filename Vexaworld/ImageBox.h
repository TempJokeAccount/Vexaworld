#pragma once
#include "SimpleSDLWrapper.h"
#include "GameObject.h"
#include "Scene.h"

class ImageBox : public GameObject
{
public:
	Image* image;
	double angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	ImageBox(Scene* scene, float x, float y, int width, int height, std::string path) : GameObject(scene, x, y, width, height) {
		image = new Image(scene->renderer, path);
	};
	ImageBox(Scene* scene, float x, float y, int width, int height, std::string path, double angle, SDL_RendererFlip flip) : GameObject(scene, x, y, width, height), flip(flip), angle(angle) {
		image = new Image(scene->renderer, path);
	};
	virtual void render() {
		renderer->drawImage(image, x - scene->cameraX, y - scene->cameraY, width, height, angle, flip);
	}
};