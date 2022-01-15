#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "lesson3.hpp"

namespace sdl_lazyfoo
{
namespace lesson4
{
namespace
{
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL,
};

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* current_surface = nullptr;

} // namespace

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("SDL Tutorial Lesson 4", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            screen_surface = SDL_GetWindowSurface(window);
        }
    }
    return success;
}

bool loadSurface(SDL_Surface* surface_to_load, const std::string& path)
{
    surface_to_load = SDL_LoadBMP(path.c_str());
    if (surface_to_load == nullptr) {
        std::cerr << "Unable to load image for path: " << path << " error: " << SDL_GetError()
                  << std::endl;
        return false;
    }
    return true;
}

bool loadMedia()
{
    bool success = true;
    /* Note: This path MUST be set to the executable WORKING directory,
    so copy the images directory into the build/bin if necessary*/
    success = loadSurface(key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT],
                          "images/default.bmp");

    return success;
}

void close()
{
    SDL_FreeSurface(lenna_surface);
    lenna_surface = nullptr;

    // screen_surface is destroyed together with the window
    SDL_DestroyWindow(window);
    window = nullptr;

    SDL_Quit();
}

void lesson4()
{
    if (!init()) {
        std::cerr << "Failed to initialize\n";
    } else {
        if (!loadMedia()) {
            std::cerr << "Failed to load media\n";
        } else {
            bool quit = false;
            SDL_Event e;
            while (!quit) {
                while (SDL_PollEvent(&e) != 0) {
                    if (e.type == SDL_QUIT) {
                        quit = true;
                    }
                }
            }

            SDL_BlitSurface(lenna_surface, nullptr, screen_surface, nullptr);
            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
        }
    }
    close();
}

} // namespace lesson4
} // namespace sdl_lazyfoo