#include <iostream>
#include <string>

#include "lesson10.hpp"
#include "texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson10
{
namespace
{

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 700;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Texture* background_texture;
Texture* lad_texture;

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
        background_texture = new Texture(renderer);
        lad_texture = new Texture(renderer);
        if (background_texture == nullptr || lad_texture == nullptr) {
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

  if (!lad_texture->LoadFromFile("images/lad.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  if (!background_texture->LoadFromFile("images/background.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  lad_texture->DeallocateTexture();
  background_texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson10()
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

        // Render background texture to screen
        background_texture->Render(0, 0);

        // Render Foo' to the screen
        lad_texture->Render(240, 190);

        // Update screen
        SDL_RenderPresent(renderer);
      }

      SDL_Delay(1000);
    }
  }
  close();
  delete background_texture;
  delete lad_texture;
}

} // namespace lesson10
} // namespace sdl_lazyfoo