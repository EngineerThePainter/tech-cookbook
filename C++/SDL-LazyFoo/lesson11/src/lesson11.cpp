#include <iostream>
#include <string>

#include "lesson11/lesson11.hpp"
#include "lesson11/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson11
{
namespace
{

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect sprite_clips[4];
Texture* sheet_texture;

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
        sheet_texture = new Texture(renderer);
        if (sheet_texture == nullptr) {
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

  if (!sheet_texture->LoadFromFile("images/dots.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  } else {
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 100;
    sprite_clips[0].h = 100;

    sprite_clips[1].x = 100;
    sprite_clips[1].y = 0;
    sprite_clips[1].w = 100;
    sprite_clips[1].h = 100;

    sprite_clips[2].x = 0;
    sprite_clips[2].y = 100;
    sprite_clips[2].w = 100;
    sprite_clips[2].h = 100;

    sprite_clips[3].x = 100;
    sprite_clips[3].y = 100;
    sprite_clips[3].w = 100;
    sprite_clips[3].h = 100;
  }

  return success;
}

void close()
{
  sheet_texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson11()
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
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        sheet_texture->Render(0, 0, &sprite_clips[0]);
        sheet_texture->Render(SCREEN_WIDTH - sprite_clips[1].w, 0, &sprite_clips[1]);
        sheet_texture->Render(0, SCREEN_HEIGHT - sprite_clips[2].h, &sprite_clips[2]);
        sheet_texture->Render(SCREEN_WIDTH - sprite_clips[3].w, SCREEN_HEIGHT - sprite_clips[3].h, &sprite_clips[3]);

        // Update screen
        SDL_RenderPresent(renderer);
      }

      SDL_Delay(1000);
    }
  }
  close();
  delete sheet_texture;
}

} // namespace lesson11
} // namespace sdl_lazyfoo