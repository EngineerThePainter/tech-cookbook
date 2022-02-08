#include <iostream>
#include <string>

#include "lesson17/button.hpp"
#include "lesson17/lesson17.hpp"
#include "lesson17/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson17
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Texture* texture = nullptr;
Button buttons[TOTAL_BUTTONS];
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

        for (size_t i = 0; i < TOTAL_BUTTONS; ++i) {
          buttons[i].SetTexture(*texture);
        }
      }
    }
  }
  return success;
}

bool loadMedia()
{
  bool success = true;

  if (!texture->LoadFromFile("images/mouse.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  } else {
    // Set buttons in corners
    buttons[0].SetPosition(0, 0);
    buttons[1].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH, 0);
    buttons[2].SetPosition(0, SCREEN_HEIGHT - BUTTON_HEIGHT);
    buttons[3].SetPosition(SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
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

void lesson17()
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

          for (size_t i = 0; i < TOTAL_BUTTONS; ++i) {
            buttons[i].HandleEvent(&e);
          }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        for (size_t i = 0; i < TOTAL_BUTTONS; ++i) {
          buttons[i].Render();
        }

        // Update screen
        SDL_RenderPresent(renderer);
      }
      // SDL_Delay(1000);
    }
    close();
    delete texture;
  }
}

} // namespace lesson17
} // namespace sdl_lazyfoo