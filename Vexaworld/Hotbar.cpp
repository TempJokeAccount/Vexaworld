#include "Hotbar.h"
#include "defs.h"

Hotbar::Hotbar(Scene *scene) : scene(scene) {
    blocks.push_back({.image = scene->game->getImage("block.png")});
}

void Hotbar::render() {
    auto renderer = scene->renderer;
    Dimensions dimentions = renderer->getDimensions();

    int x = dimentions.width / 2 - HOTBAR_WIDTH / 2;
    int y = dimentions.height - HOTBAR_HEIGHT - HOTBAR_PADDING;

    // border
    renderer->setColor(0xFF, 0x00, 0xFF, 0xFF);
    renderer->fillRect(x - 1, y - 1, HOTBAR_WIDTH + 2, HOTBAR_HEIGHT + 2);

    // content
    renderer->setColor(0x00, 0x00, 0x00, 0xFF);
    renderer->fillRect(x, y, HOTBAR_WIDTH, HOTBAR_HEIGHT);

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