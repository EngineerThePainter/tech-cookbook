#include <iostream>
#include <string>

#include "lesson14/lesson14.hpp"
#include "lesson14/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>

namespace sdl_lazyfoo
{
namespace lesson14
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
Texture* texture;
const int walking_animation_frames = 4;
SDL_Rect sprite_clips[walking_animation_frames];

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
      }
    }
  }
  return success;
}

bool loadMedia()
{
  bool success = true;

  if (!texture->LoadFromFile("images/anim.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  } else {
    sprite_clips[0].x = 0;
    sprite_clips[0].y = 0;
    sprite_clips[0].w = 160;
    sprite_clips[0].h = 400;

    sprite_clips[1].x = 160;
    sprite_clips[1].y = 0;
    sprite_clips[1].w = 160;
    sprite_clips[1].h = 400;

    sprite_clips[2].x = 320;
    sprite_clips[2].y = 0;
    sprite_clips[2].w = 160;
    sprite_clips[2].h = 400;

    sprite_clips[3].x = 480;
    sprite_clips[3].y = 0;
    sprite_clips[3].w = 160;
    sprite_clips[3].h = 400;
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

void lesson14()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;

      int frame = 0;

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
          }
        }
        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);
        std::cerr << frame / 4 << std::endl;
        SDL_Rect* current_clip = &sprite_clips[frame / 4];
        texture->Render((SCREEN_WIDTH - current_clip->w) / 2, (SCREEN_HEIGHT - current_clip->h) / 2, current_clip);
        // Update screen
        SDL_RenderPresent(renderer);
        ++frame;
        if (frame / 4 >= walking_animation_frames) {
          frame = 0;
        }
      }
      // SDL_Delay(1000);
    }
    close();
    delete texture;
  }
}

} // namespace lesson14
} // namespace sdl_lazyfoo