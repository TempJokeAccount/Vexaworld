#pragma once
#include "Game.h"
#include "SDL.h"

class Window {
  public:
    Window(Game *game);
    virtual ~Window(){};
    int x, y, width, height;
    Game *game;
    void render();
    virtual void update() = 0;
    virtual void renderContent(int x, int y, int width, int height) = 0;
    virtual void handleEvent(SDL_Event &event);
    virtual void handleContentEvent(SDL_Event &event) = 0;

  private:
    bool isDragged = false;
    int lastDragX = 0;
    int lastDragY = 0;
};