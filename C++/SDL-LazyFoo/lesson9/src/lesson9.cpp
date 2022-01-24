#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "lesson9.hpp"

namespace sdl_lazyfoo
{
namespace lesson9
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
    window = SDL_CreateWindow("SDL Tutorial Lazy Foo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
      if (renderer == nullptr) {
        std::cerr << "Renderer could not be created. Error: " << SDL_GetError() << std::endl;
        success = false;
      } else {
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          std::cerr << "SDL image could not initialize. Error: " << SDL_GetError() << std::endl;
          success = false;
        }
      }
    }
  }
  return success;
}

SDL_Texture* loadTexture(const std::string& path)
{
  SDL_Texture* newTexture = nullptr;
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == nullptr) {
    std::cerr << "Unable to load image " << path << " caused by error: " << IMG_GetError();
  } else {
    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (newTexture == nullptr) {
      std::cerr << "Unable to create texture from: " << path << " caused by error: " << SDL_GetError();
    }
    SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}

bool loadMedia()
{
  bool success = true;
  texture = loadTexture("images/texture.png");
  if (texture == nullptr) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

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

void lesson9()
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

        // Top Left Viewport
        // x, y, w, h
        SDL_Rect top_left_viewport{0, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &top_left_viewport);
        // Render copy to the screen
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // Top Right Viewport
        SDL_Rect top_right_viewport{SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &top_right_viewport);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        // Bottom Viewport
        SDL_Rect bottom_viewport{0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
        SDL_RenderSetViewport(renderer, &bottom_viewport);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);

        SDL_RenderPresent(renderer);
      }

      SDL_Delay(1000);
    }
  }
  close();
}

} // namespace lesson9
} // namespace sdl_lazyfoo