#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "lesson8.hpp"

namespace sdl_lazyfoo
{
namespace lesson8
{
namespace
{

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* texture = nullptr;

} // namespace

bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
        success = false;
    } else {
        window = SDL_CreateWindow("SDL Tutorial Lazy Foo", SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if (window == nullptr) {
            std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
            success = false;
        } else {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == nullptr) {
                std::cerr << "Renderer could not be created. Error: " << SDL_GetError()
                          << std::endl;
                success = false;
            }
        }
    }
    return success;
}

// Intentionally left empty to mark that we are not loading any media in this lesson
bool loadMedia()
{
    bool success = true;
    return success;
}

void close()
{
    SDL_DestroyTexture(texture);
    texture = nullptr;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;

    IMG_Quit();
    SDL_Quit();
}

void lesson8()
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
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                // Clear screen
                SDL_RenderClear(renderer);

                // Render red filled quad
                SDL_Rect fillRect = {SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2,
                                     SCREEN_HEIGHT / 2};
                SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
                SDL_RenderFillRect(renderer, &fillRect);

                // Render green filled quad
                SDL_Rect outlineRect = {SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3,
                                        SCREEN_HEIGHT * 2 / 3};
                SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
                SDL_RenderDrawRect(renderer, &outlineRect);

                // Blue horizontal line
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
                SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

                // Yellow vertical dotted line
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
                for (int i = 0; i < SCREEN_WIDTH; i += 4) {
                    SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, i);
                }

                // Update screen
                SDL_RenderPresent(renderer);
            }

            SDL_Delay(1000);
        }
    }
    close();
}

} // namespace lesson8
} // namespace sdl_lazyfoo