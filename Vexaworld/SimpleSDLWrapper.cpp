#include "SimpleSDLWrapper.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

// Dont wanna use a C library

SimpleSDLWrapper::SimpleSDLWrapper(std::string name, int w, int h)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
};

SimpleSDLWrapper::~SimpleSDLWrapper() 
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
};

void SimpleSDLWrapper::setColor(int r, int g, int b, int a) 
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
};

void SimpleSDLWrapper::fillRect(int x, int y, int w, int h) 
{
    SDL_Rect rect = {};
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
};

void SimpleSDLWrapper::drawImage(Image* image, int x, int y, int w, int h)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, image->texture, NULL, &rect);
};

void SimpleSDLWrapper::drawImage(Image* image, int x, int y, int w, int h, double rot, SDL_RendererFlip flip)
{
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopyEx(renderer, image->texture, NULL, &rect, rot, NULL, flip);
};

void SimpleSDLWrapper::clear() 
{
    SDL_RenderClear(renderer);
};

void SimpleSDLWrapper::present() 
{
    SDL_RenderPresent(renderer);
};

void SimpleSDLWrapper::delay(int ms) 
{
    SDL_Delay(ms);
};

dimentions SimpleSDLWrapper::getDimentions()
{
    int* widthPointer = new int;
    int* heightPointer = new int;
    SDL_GetRendererOutputSize(renderer, widthPointer, heightPointer);
    int width = *widthPointer;
    int height = *heightPointer;
    delete widthPointer, heightPointer;
    return { width, height };
}

Image::Image(SimpleSDLWrapper* wrapper, std::string path) {
    texture = IMG_LoadTexture(wrapper->renderer, path.c_str());
    if (!texture) printf(IMG_GetError());
}

Image::~Image()
{
    SDL_DestroyTexture(texture);
}

void Image::setAlpha(uint8_t alpha)
{
    SDL_SetTextureAlphaMod(texture, alpha);
}