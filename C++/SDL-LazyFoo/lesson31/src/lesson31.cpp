#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson31/dot.hpp"
#include "lesson31/lesson31.hpp"
#include "lesson31/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson31
{
namespace
{

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

std::unique_ptr<Texture> texture;
std::unique_ptr<Texture> background_texture;
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

    window = SDL_CreateWindow("SDL Tutorial Lazy Foo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              Dot::SCREEN_WIDTH, Dot::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

        background_texture = std::make_unique<Texture>(renderer);
        if (background_texture == nullptr) {
          std::cerr << "Background texture failed to load";
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
    std::cerr << "Failed to load texturr, error: " << SDL_GetError() << std::endl;
    success = false;
  }
  texture->SetWidth(Dot::DOT_WIDTH);
  texture->SetHeight(Dot::DOT_HEIGHT);

  if (!background_texture->LoadFromFile("images/scrolling_background.png")) {
    std::cerr << "Failed to load background texture, error: " << SDL_GetError() << std::endl;
    success = false;
  }
  background_texture->SetWidth(Dot::SCREEN_WIDTH);
  background_texture->SetHeight(Dot::SCREEN_HEIGHT);

  return success;
}

void close()
{
  texture->DeallocateTexture();
  background_texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void lesson31()
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

      Dot dot(0, 0, *texture);

      // SDL_Rect camera = {0, 0, Dot::SCREEN_WIDTH, Dot::SCREEN_HEIGHT};

      int scrollingOffset = 0;

      while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          dot.handleEvent(e);
        }

        dot.move();

        --scrollingOffset;
        if (scrollingOffset < -background_texture->GetWidth()) {
          scrollingOffset = 0;
        }

        // // Center camera over the dot
        // camera.x = (dot.getX() + Dot::DOT_WIDTH / 2) - Dot::SCREEN_WIDTH / 2;
        // camera.y = (dot.getY() + Dot::DOT_HEIGHT / 2) - Dot::SCREEN_HEIGHT / 2;

        // // Keep camera in bounds
        // if (camera.x < 0) {
        //   camera.x = 0;
        // }
        // if (camera.y < 0) {
        //   camera.y = 0;
        // }
        // if (camera.x > Dot::LEVEL_WIDTH - camera.w) {
        //   camera.x = Dot::LEVEL_WIDTH - camera.w;
        // }
        // if (camera.y > Dot::LEVEL_HEIGHT - camera.h) {
        //   camera.y = Dot::LEVEL_HEIGHT - camera.h;
        // }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background_texture->Render(scrollingOffset, 0);
        background_texture->Render(scrollingOffset + background_texture->GetWidth(), 0);

        dot.render();

        SDL_RenderPresent(renderer);
      }
      close();
    }
  }
}
} // namespace lesson31
} // namespace sdl_lazyfoo