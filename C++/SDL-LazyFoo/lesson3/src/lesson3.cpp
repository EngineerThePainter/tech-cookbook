#include "lesson3.hpp"

#include <iostream>

#include "SDL2/SDL.h"

namespace sdl_lazyfoo
{
namespace lesson3
{
namespace
{
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* lenna_surface = nullptr;
} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    window =
        SDL_CreateWindow("SDL Tutorial Lesson 3", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      screen_surface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

bool loadMedia()
{
  bool success = true;
  /* Nore: This path MUST be set to the executable WORKING directory,
  so copy the images directory into the build/bin if necessary*/
  lenna_surface = SDL_LoadBMP("images/lenna.bmp");
  if (lenna_surface == nullptr) {
    std::cerr << "Unable to load image: " << SDL_GetError() << std::endl;
    success = false;
  }
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

void lesson3()
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

} // namespace lesson3
} // namespace sdl_lazyfoo