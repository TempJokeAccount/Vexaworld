#pragma once
#include <SDL.h>
#include <string>
#include "defs.h"

class SimpleSDLWrapper;

class Image {
    friend SimpleSDLWrapper;

  public:
    Image(SimpleSDLWrapper *wrapper, std::string path);
    ~Image();
    void setAlpha(uint8_t alpha);

  private:
    SDL_Texture *texture;
};

class SimpleSDLWrapper {
    friend Image;

  public:
    SimpleSDLWrapper(std::string, int, int);
    ~SimpleSDLWrapper();
    void setColor(int red, int green, int blue, int alpha);
    void fillRect(int x, int y, int width, int height);
    void drawImage(Image *, int x, int y, int width, int height);
    void drawImage(Image *, int x, int y, int width, int height, double angle, SDL_RendererFlip flip);
    void present();
    void clear();
    void delay(int);
    Dimensions getDimensions();

  private:
    SDL_Renderer *renderer;
    SDL_Window *window;
};