#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson26/lesson26.hpp"
#include "lesson26/texture.hpp"
#include "lesson26/timer.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson26
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

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

void lesson26()
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

      Timer fps_counter;
      Timer cap_timer;
      std::stringstream time_text;

      int counted_frames = 0;
      fps_counter.Start();

      while (!quit) {
        cap_timer.Start();

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }

        float average_fps = counted_frames / (fps_counter.GetTicks() / 1000.0f);
        if (average_fps > 2000000) {
          average_fps = 0;
        }

        time_text.str("");
        time_text << "Average fps per second (with cap)" << average_fps;
        texture->LoadFromRenderedText(time_text.str(), text_color);

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        texture->Render(0, (SCREEN_HEIGHT) / 2);
        SDL_RenderPresent(renderer);
        ++counted_frames;

        // We are introducing here waiting mechanism that will block rendering frame for a time required to keep correct
        // FPS without that it would be not bounded by any way.
        int frame_ticks = cap_timer.GetTicks();
        if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
          SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
        }
      }
      close();
    }
  }
}
} // namespace lesson26
} // namespace sdl_lazyfoo