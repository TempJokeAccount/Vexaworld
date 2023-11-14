// TODO: Make this better

#include "PixelDrawer.h"
#include "GameObject.h"
#include "SimpleSDLWrapper.h"
#include "defs.h"
#include <cmath>

PixelDrawer::PixelDrawer(Game *game) : Window(game), canvas(PixelDrawerCanvas(game->renderer, this)) {
    width = 300;
    height = 400;
}

void PixelDrawer::renderContent(int x, int y, int width, int height) {
    canvas.render(x + 10, y + 10, width - 20, width - 20);
}

void PixelDrawer::handleContentEvent(SDL_Event &event, SDL_Point mouse) {
    if (leftMouseHeld) {
        SDL_Point pixel = canvas.getPixelPosAt(mouse.x - 10, mouse.y - 10);
        if (pixel.x != -1) {
            canvas.pixels[pixel.x][pixel.y] = {0xFF, 0xFF, 0xFF, 0xFF};
        }
    }
}

void PixelDrawer::update() {
}

PixelDrawerCanvas::PixelDrawerCanvas(SimpleSDLWrapper *renderer, PixelDrawer *window) : renderer(renderer), window(window) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            pixels[i][j] = {0, 0, 0, 0};
        }
    }
}

PixelDrawerCanvas::~PixelDrawerCanvas() {
    // Aparently dont have to free the array here :-/
}

void PixelDrawerCanvas::render(float x, float y, float width, float height) {
    renderer->setColor(0x00, 0x00, 0x00, 0xFF);
    renderer->fillRect(x, y, width, height);
    float pixelSize = width / BLOCK_SIZE;
    for (int i = 0; i < BLOCK_SIZE; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            RGBA pixel = pixels[i][j];
            renderer->setColor(pixel.r, pixel.g, pixel.b, pixel.a);
            renderer->fillRect(
                x + i * pixelSize,
                y + j * pixelSize,
                pixelSize + 1,
                pixelSize + 1);
        }
    }
}

SDL_Point PixelDrawerCanvas::getPixelPosAt(int x, int y) {
    int mySize = window->width - 20;
    if (x < 0 || y < 0 || x > mySize || y > mySize) {
        return {-1};
    }
    return {
        int(x / ((float)mySize / BLOCK_SIZE)),
        int(y / ((float)mySize / BLOCK_SIZE)),
    };
}