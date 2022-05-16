#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson30/dot.hpp"
#include "lesson30/lesson30.hpp"
#include "lesson30/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson30
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
  texture->SetWidth(20);
  texture->SetHeight(20);

  if (!background_texture->LoadFromFile("images/scrolling_background.png")) {
    std::cerr << "Failed to load background texture, error: " << SDL_GetError() << std::endl;
    success = false;
  }
  texture->SetWidth(Dot::LEVEL_WIDTH);
  texture->SetHeight(Dot::LEVEL_HEIGHT);

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

void lesson30()
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

      SDL_Rect camera = {0, 0, Dot::SCREEN_WIDTH, Dot::SCREEN_HEIGHT};

      while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          dot.handleEvent(e);
        }

        dot.move();

        // Center camera over the dot
        camera.x = (dot.getX() + Dot::DOT_WIDTH / 2) - Dot::SCREEN_WIDTH / 2;
        camera.y = (dot.getY() + Dot::DOT_HEIGHT / 2) - Dot::SCREEN_HEIGHT / 2;

        // Keep camera in bounds
        if (camera.x < 0) {
          camera.x = 0;
        }
        if (camera.y < 0) {
          camera.y = 0;
        }
        if (camera.x > Dot::LEVEL_WIDTH - camera.w) {
          camera.x = Dot::LEVEL_WIDTH - camera.w;
        }
        if (camera.y > Dot::LEVEL_HEIGHT - camera.h) {
          camera.y = Dot::LEVEL_HEIGHT - camera.h;
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        background_texture->Render(0, 0, &camera);

        dot.render(camera.x, camera.y);

        SDL_RenderPresent(renderer);
      }
      close();
    }
  }
}
} // namespace lesson30
} // namespace sdl_lazyfoo