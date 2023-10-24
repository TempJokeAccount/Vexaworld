#pragma once
#include "SimpleSDLWrapper.h"
#include "GameObject.h"
#include "Game.h"

class ImageBox : public GameObject
{
public:
	Image* image;
	double angle = 0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	ImageBox(Game* game, float x, float y, int width, int height, std::string path) : GameObject(game, x, y, width, height) {
		image = new Image(game->renderer, path);
	};
	ImageBox(Game* game, float x, float y, int width, int height, std::string path, double angle, SDL_RendererFlip flip) : GameObject(game, x, y, width, height), flip(flip), angle(angle) {
		image = new Image(game->renderer, path);
	};
	virtual void render() {
		renderer->drawImage(image, x - game->cameraX, y - game->cameraY, width, height, angle, flip);
	}
};