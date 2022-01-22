#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "lesson6.hpp"

namespace sdl_lazyfoo
{
namespace lesson6
{
namespace
{

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window* window = nullptr;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* current_surface = nullptr;

} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    window =
        SDL_CreateWindow("SDL Tutorial Lesson 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      // Initialize PNG images
      int imgFlags = IMG_INIT_PNG;
      if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cerr << "SDL image could not initialize. SDL image error: " << IMG_GetError()
                  << std::endl;
        success = false;
      } else {
        screen_surface = SDL_GetWindowSurface(window);
      }
    }
  }
  return success;
}

SDL_Surface* loadSurface(const std::string& path)
{
  SDL_Surface* optimized_surface = nullptr;

  SDL_Surface* loaded_surface = IMG_Load(path.c_str());
  if (loaded_surface == nullptr) {
    std::cerr << "Unable to load image for path: " << path << " error: " << SDL_GetError()
              << std::endl;
  } else {
    // Convert surface to screen format
    optimized_surface = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
    if (optimized_surface == nullptr) {
      std::cerr << "Unable optimize surface: " << path << " error: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(loaded_surface);
  }
  return optimized_surface;
}

bool loadMedia()
{
  bool success = true;
  current_surface = loadSurface("images/png-image.png");
  if (current_surface == nullptr) {
    std::cerr << "Cannot load surface, error: " << SDL_GetError() << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  SDL_FreeSurface(current_surface);

  // screen_surface is destroyed together with the window
  SDL_DestroyWindow(window);
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson6()
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
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(current_surface, nullptr, screen_surface, &stretchRect);
        SDL_UpdateWindowSurface(window);
      }

      SDL_Delay(1000);
    }
  }
  close();
}

} // namespace lesson6
} // namespace sdl_lazyfoo