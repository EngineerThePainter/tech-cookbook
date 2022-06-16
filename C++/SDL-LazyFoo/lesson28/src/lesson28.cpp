#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson28/dot.hpp"
#include "lesson28/lesson28.hpp"
#include "lesson28/texture.hpp"
#include "lesson28/timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson28
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

std::unique_ptr<Texture> texture;
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
      // Disabled V-Sync to do it manually
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

        if (TTF_Init() == -1) {
          std::cerr << "SDL TTF could not initialize. Error: " << TTF_GetError() << std::endl;
          success = false;
        }

        texture = std::make_unique<Texture>(renderer);
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

  if (!texture->LoadFromFile("images/dot.png")) {
    std::cerr << "Failed to load text, error: " << TTF_GetError() << std::endl;
    success = false;
  }
  texture->SetWidth(20);
  texture->SetHeight(20);

  return success;
}

void close()
{
  texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void lesson28()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      // Main loop flag
      bool quit = false;
      SDL_Event e;
      SDL_Color text_color = {0, 0, 0, 255};

      Dot dot(0, 0, *texture);

      Dot otherDot(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, *texture);

      while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          dot.handleEvent(e);
        }

        dot.move(otherDot.getColliders());

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);

        dot.render();
        otherDot.render();

        SDL_RenderPresent(renderer);
      }
      close();
    }
  }
}
} // namespace lesson28
} // namespace sdl_lazyfoo