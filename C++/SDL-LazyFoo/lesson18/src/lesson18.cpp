#include <iostream>
#include <memory>
#include <string>

#include "lesson18/button.hpp"
#include "lesson18/lesson18.hpp"
#include "lesson18/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson18
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
std::unique_ptr<Texture> left_arrow;
std::unique_ptr<Texture> up_arrow;
std::unique_ptr<Texture> down_arrow;
std::unique_ptr<Texture> right_arrow;
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

        left_arrow = std::make_unique<Texture>(renderer);
        right_arrow = std::make_unique<Texture>(renderer);
        up_arrow = std::make_unique<Texture>(renderer);
        down_arrow = std::make_unique<Texture>(renderer);
        if (left_arrow == nullptr || right_arrow == nullptr || up_arrow == nullptr || down_arrow == nullptr) {
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

  if (!left_arrow->LoadFromFile("images/left.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  if (!right_arrow->LoadFromFile("images/right.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  if (!up_arrow->LoadFromFile("images/up.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  if (!down_arrow->LoadFromFile("images/down.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  up_arrow->DeallocateTexture();
  down_arrow->DeallocateTexture();
  left_arrow->DeallocateTexture();
  right_arrow->DeallocateTexture();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  renderer = nullptr;
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson18()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;
      Texture* current_texture = up_arrow.get();

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }

          const Uint8* current_key_states = SDL_GetKeyboardState(nullptr);
          if (current_key_states[SDL_SCANCODE_UP]) {
            current_texture = up_arrow.get();
          }
          if (current_key_states[SDL_SCANCODE_DOWN]) {
            current_texture = down_arrow.get();
          }
          if (current_key_states[SDL_SCANCODE_LEFT]) {
            current_texture = left_arrow.get();
          }
          if (current_key_states[SDL_SCANCODE_RIGHT]) {
            current_texture = right_arrow.get();
          }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        current_texture->Render(0, 0);
        // Update screen
        SDL_RenderPresent(renderer);
      }
      // SDL_Delay(1000);
    }
    close();
  }
}

} // namespace lesson18
} // namespace sdl_lazyfoo