#include <iostream>
#include <string>

#include "lesson16/lesson16.hpp"
#include "lesson16/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson16
{
namespace
{

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Texture* texture = nullptr;

} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      std::cerr << "Warning: Linear texture filtering not enabled!";
    }

    window = SDL_CreateWindow("SDL Tutorial Lazy Foo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
        texture = new Texture(renderer);
        if (texture == nullptr) {
          std::cerr << "Textures failed to create";
          success = false;
        }
      }
    }
  }
  return success;
}

bool loadMedia()
{
  bool success = true;

  if (!texture->LoadFromFile("images/arrow.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson16()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;

      double degrees = 0.0;
      SDL_RendererFlip flip_type = SDL_FLIP_NONE;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_a:
              degrees -= 60.0;
              break;
            case SDLK_d:
              degrees += 60.0;
              break;
            case SDLK_q:
              flip_type = SDL_FLIP_HORIZONTAL;
              break;
            case SDLK_w:
              flip_type = SDL_FLIP_NONE;
              break;
            case SDLK_e:
              flip_type = SDL_FLIP_VERTICAL;
              break;
            }
          }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        texture->Render((SCREEN_WIDTH - texture->GetWidth()) / 2, (SCREEN_HEIGHT - texture->GetHeight()) / 2, nullptr,
                        degrees, nullptr, flip_type);

        // Update screen
        SDL_RenderPresent(renderer);
      }
      // SDL_Delay(1000);
    }
    close();
    delete texture;
  }
}

} // namespace lesson16
} // namespace sdl_lazyfoo