#pragma once
#include "Window.h"
#include "SimpleSDLWrapper.h"
#include "defs.h"

struct RGBA {
    uint8_t r, g, b, a;
};

class PixelDrawer;

class PixelDrawerCanvas {
  public:
    SimpleSDLWrapper *renderer;
    PixelDrawer *window;
    PixelDrawerCanvas(SimpleSDLWrapper *renderer, PixelDrawer *window);
    ~PixelDrawerCanvas();
    RGBA pixels[BLOCK_SIZE][BLOCK_SIZE]{};
    void render(float x, float y, float width, float height);
    Point getPixelPosAt(int x, int y);
};

class PixelDrawer final : public Window {
  public:
    PixelDrawer(Game *game);
    PixelDrawerCanvas canvas;
    virtual void renderContent(int x, int y, int width, int height) override;
    virtual void handleContentEvent(SDL_Event &event, Point mouse) override;
    virtual void update() override;
};