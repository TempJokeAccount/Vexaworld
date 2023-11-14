#include "Hotbar.h"
#include "defs.h"

Hotbar::Hotbar(Scene *scene) : scene(scene) {
    blocks.push_back({.image = scene->game->getImage("block.png")});
}

void Hotbar::render() {
    auto renderer = scene->renderer;
    SDL_Point dimentions = renderer->getDimensions();
    x = dimentions.x / 2 - HOTBAR_WIDTH / 2;
    y = dimentions.y - HOTBAR_HEIGHT - HOTBAR_PADDING;

    // border
    renderer->setColor(0xFF, 0x00, 0xFF, 0xFF);
    renderer->strokeRect(x - 1, y - 1, HOTBAR_WIDTH + 2, HOTBAR_HEIGHT + 2);

    // content
    renderer->setColor(0x00, 0x00, 0x00, 0xFF);
    renderer->fillRect(x, y, HOTBAR_WIDTH, HOTBAR_HEIGHT);

    // selection box
    renderer->setColor(0x00, 0x00, 0xFF, 0xFF);
    renderer->fillRect(
        x + (BLOCK_SIZE * HOTBAR_PADDING) * selectedBlockIndex,
        y,
        BLOCK_SIZE + HOTBAR_PADDING * 2,
        BLOCK_SIZE + HOTBAR_PADDING * 2);

    for (int i = 0; i < HOTBAR_BLOCKCOUNT; i++) {
        int blockX = x + HOTBAR_PADDING + (BLOCK_SIZE + HOTBAR_PADDING) * i;
        int blockY = y + HOTBAR_PADDING;

        // temp
        if (i >= blocks.size()) {
            break;
        }

        renderer->drawImage(blocks[i].image, blockX, blockY, BLOCK_SIZE, BLOCK_SIZE);
    }
}

void Hotbar::onClick(SDL_Point mouse) {
    mouse.x -= x;
    
    selectedBlockIndex = mouse.x / (HOTBAR_PADDING + BLOCK_SIZE);
}