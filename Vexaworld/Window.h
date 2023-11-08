#pragma once
#include "Game.h"
#include "SDL.h"

class Window {
  public:
    Window(Game *game);
    virtual ~Window();
    int x = 100, y = 100, width = 300, height = 200;
    bool leftMouseHeld = false;
    Game *game;
    void render();
    void handleEvent(SDL_Event &event);
    virtual void update() = 0;
    virtual void renderContent(int x, int y, int width, int height) = 0;
    virtual void handleContentEvent(SDL_Event &event, Point mouse) = 0;
  private:
    bool isDragged = false;
    int lastDragX = 0;
    int lastDragY = 0;
};