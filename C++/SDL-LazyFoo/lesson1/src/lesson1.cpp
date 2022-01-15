//#define SDL_MAIN_HANDLED

#include "lesson1.hpp"

#include <SDL2/SDL.h>

#include <iostream>

namespace sdl_lazyfoo
{
namespace
{
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
} // namespace

void lesson1()
{
    SDL_Window* window = nullptr;

    SDL_Surface* screenSurface = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! Error: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow("SDL Tutorial from LazyFoo", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cout << "Window could not initialize! Error: " << SDL_GetError() << std::endl;
        } else {
            screenSurface = SDL_GetWindowSurface(window);
            SDL_FillRect(screenSurface, nullptr,
                         SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);
            SDL_Delay(5000);
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}
} // namespace sdl_lazyfoo