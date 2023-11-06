#pragma once
#include "Window.h"

class TestWindow final : public Window {
  public:
    using Window::Window;

    virtual void renderContent(int x, int y, int width, int height) override {
        auto renderer = game->renderer;

        if (isRed) {
            renderer->setColor(0xFF, 0x00, 0x00, 0xFF);
        } else {
            renderer->setColor(0x00, 0xFF, 0x00, 0xFF);
        }

        renderer->fillRect(x, y, width, height);
    }

    virtual void handleEvent(SDL_Event &event) override {
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            isRed = !isRed;
        }
    }

    virtual void update() override {
    }

  private:
    bool isRed = false;
};