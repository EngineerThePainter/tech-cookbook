#include <iostream>
#include <string>

#include "SDL2/SDL.h"
#include "lesson5.hpp"

namespace sdl_lazyfoo
{
namespace lesson5
{
namespace
{
enum KeyPressSurfaces {
  KEY_PRESS_SURFACE_DEFAULT = 0,
  KEY_PRESS_SURFACE_UP,
  KEY_PRESS_SURFACE_DOWN,
  KEY_PRESS_SURFACE_LEFT,
  KEY_PRESS_SURFACE_RIGHT,
  KEY_PRESS_SURFACE_TOTAL,
};

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
SDL_Window* window = nullptr;
SDL_Surface* screen_surface = nullptr;
SDL_Surface* key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL];
SDL_Surface* current_surface = nullptr;

} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {
    window =
        SDL_CreateWindow("SDL Tutorial Lesson 4", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      screen_surface = SDL_GetWindowSurface(window);
    }
  }
  return success;
}

bool loadSurface(SDL_Surface** surface_to_load, const std::string& path)
{
  SDL_Surface* optimized_surface = nullptr;

  SDL_Surface* loaded_surface = SDL_LoadBMP(path.c_str());
  if (loaded_surface == nullptr) {
    std::cerr << "Unable to load image for path: " << path << " error: " << SDL_GetError()
              << std::endl;
    return false;
  } else {
    // Convert surface to screen format
    *surface_to_load = SDL_ConvertSurface(loaded_surface, screen_surface->format, 0);
    if (*surface_to_load == nullptr) {
      std::cerr << "Unable optimize surface: " << path << " error: " << SDL_GetError() << std::endl;
      return false;
    }
    SDL_FreeSurface(loaded_surface);
  }
  return true;
}

bool loadMedia()
{
  bool success = true;
  /* Note: This path MUST be set to the executable WORKING directory,
  so copy the images directory into the build/bin if necessary*/
  success = loadSurface(&key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT],
                        "images/default.bmp");
  success =
      loadSurface(&key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN], "images/down.bmp");
  success =
      loadSurface(&key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT], "images/left.bmp");
  success = loadSurface(&key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT],
                        "images/right.bmp");
  success =
      loadSurface(&key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_UP], "images/up.bmp");

  return success;
}

void close()
{
  for (int i = 0; i < KeyPressSurfaces::KEY_PRESS_SURFACE_TOTAL; ++i) {
    SDL_FreeSurface(key_press_surface[i]);
    key_press_surface[i] = nullptr;
  }

  // screen_surface is destroyed together with the window
  SDL_DestroyWindow(window);
  window = nullptr;

  SDL_Quit();
}

void lesson5()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;

      current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT];
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
            case SDLK_UP:
              std::cerr << "up\n";
              current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_UP];
              break;
            case SDLK_DOWN:
              std::cerr << "down\n";
              current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DOWN];
              break;
            case SDLK_LEFT:
              std::cerr << "left\n";
              current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_LEFT];
              break;
            case SDLK_RIGHT:
              std::cerr << "right\n";
              current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_RIGHT];
              break;
            default:
              std::cerr << "default\n";
              current_surface = key_press_surface[KeyPressSurfaces::KEY_PRESS_SURFACE_DEFAULT];
              break;
            }
          }
        }
        SDL_Rect stretchRect;
        stretchRect.x = 0;
        stretchRect.y = 0;
        stretchRect.w = SCREEN_WIDTH;
        stretchRect.h = SCREEN_HEIGHT;
        SDL_BlitScaled(current_surface, nullptr, screen_surface, &stretchRect);
        SDL_UpdateWindowSurface(window);
      }

      SDL_Delay(1000);
    }
  }
  close();
}

} // namespace lesson5
} // namespace sdl_lazyfoo