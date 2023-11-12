#include "Hotbar.h"

Hotbar::Hotbar(Scene *scene) : scene(scene) {
    blocks.push_back({scene->game->getImage("block.png")});
}