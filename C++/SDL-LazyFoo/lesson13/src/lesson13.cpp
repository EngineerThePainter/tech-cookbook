#include <iostream>
#include <string>

#include "lesson13/lesson13.hpp"
#include "lesson13/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson13
{
namespace
{

const int SCREEN_WIDTH = 499;
const int SCREEN_HEIGHT = 332;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Texture* texture;
Texture* background_texture;

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
        texture = new Texture(renderer);
        background_texture = new Texture(renderer);
        if (texture == nullptr || background_texture == nullptr) {
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

  if (!texture->LoadFromFile("images/texture.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  } else {
    texture->SetBlendMode(SDL_BLENDMODE_BLEND);
  }

  if (!background_texture->LoadFromFile("images/png-image.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  texture->DeallocateTexture();
  background_texture->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson13()
{
  const Uint8 modulation_value{32};
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;

      Uint8 modulation = 255;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            // Increase alpha when w
            if (e.key.keysym.sym == SDLK_w) {
              if (modulation + 32 > 255) {
                modulation = 255;
              } else {
                modulation += 32;
              }
            }

            if (e.key.keysym.sym == SDLK_s) {
              if (modulation - 32 < 0) {
                modulation = 0;
              } else {
                modulation -= 32;
              }
            }
          }
          // Clear screen
          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
          SDL_RenderClear(renderer);

          background_texture->Render(0, 0);

          texture->SetAlpha(modulation);
          texture->Render(0, 0);
          // Update screen
          SDL_RenderPresent(renderer);
        }

        SDL_Delay(1000);
      }
    }
    close();
    delete texture;
    delete background_texture;
  }
}

} // namespace lesson13
} // namespace sdl_lazyfoo