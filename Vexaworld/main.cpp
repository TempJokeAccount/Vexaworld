#include "SimpleSDLWrapper.h"
#include "defs.h"
#include "Game.h"
#include "Player.h"

void mainLoop(Game& game) 
{
    SDL_Event event;
    bool quit = false;
    uint32_t lastTick = 0;
    float deltaTime;
    while (!quit) 
    {
        while (SDL_PollEvent(&event) != 0) 
        {
            game.handleEvent(event, &quit);
        }

        uint32_t currentTick = SDL_GetTicks();
        if (!lastTick)
        {
            lastTick = currentTick;
        }
        deltaTime = currentTick - lastTick;
        lastTick = currentTick;

        game.update(deltaTime);
        game.render(deltaTime);
        game.renderer->delay(1);
    }
}

int main(int argc, char* argv[])
{
    SimpleSDLWrapper* renderer = new SimpleSDLWrapper("Hostaworld", SCREEN_WIDTH, SCREEN_HEIGHT);
    Game game = Game(renderer);
    mainLoop(game);
    return 0;
}