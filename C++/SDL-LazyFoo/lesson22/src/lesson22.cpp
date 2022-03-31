#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson22/lesson22.hpp"
#include "lesson22/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson22
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

  if (!texture->LoadTextFromfile("images/lazy.ttf")) {
    std::cerr << "Failed to load text, error: " << TTF_GetError() << std::endl;
    success = false;
  }

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

void lesson22()
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

      Uint32 start_time = 0;
      std::stringstream time_text;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
            start_time = SDL_GetTicks();
          }
        }

        time_text.str("");
        time_text << "Milliseconds since start time " << SDL_GetTicks() - start_time;
        texture->LoadFromRenderedText(time_text.str(), text_color);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        texture->Render(0, (SCREEN_HEIGHT) / 2);
        SDL_RenderPresent(renderer);
        // SDL_Delay(1000);
      }
      close();
    }
  }
}
} // namespace lesson22
} // namespace sdl_lazyfoo