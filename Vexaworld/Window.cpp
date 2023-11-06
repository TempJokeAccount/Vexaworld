#include "Window.h"
#include "Game.h"
#include "defs.h"

Window::Window(Game *game) : game(game) {
    x = 100;
    y = 100;
    width = 100;
    height = 100;
}

void Window::render() {
    auto renderer = game->renderer;

    // background
    renderer->setColor(0xFF, 0xFF, 0xFF, 0xFF);
    renderer->fillRect(x, y, width, height);

    // titlebar
    renderer->setColor(0x6D, 0x6D, 0x6D, 0xFF);
    renderer->fillRect(x, y, width, WINDOW_TITLEBAR_HEIGHT);

    renderContent(x, y + WINDOW_TITLEBAR_HEIGHT, width, height - WINDOW_TITLEBAR_HEIGHT);
}