#include <iostream>
#include <memory>
#include <string>

#include "lesson19/lesson19.hpp"
#include "lesson19/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_joystick.h>

namespace sdl_lazyfoo
{
namespace lesson19
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JOYSTICK_DEAD_ZONE = 8000;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Joystick* game_controller = nullptr;

std::unique_ptr<Texture> arrow;
} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      std::cerr << "Warning: Linear texture filtering not enabled!";
    }

    if (SDL_NumJoysticks() < 1) {
      std::cerr << "No joysticks connected!";
    } else {
      game_controller = SDL_JoystickOpen(0);
      if (game_controller == nullptr) {
        std::cerr << "Could not open the game controller. Error: " << SDL_GetError() << std::endl;
      }
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

        arrow = std::make_unique<Texture>(renderer);
        if (arrow == nullptr) {
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

  if (!arrow->LoadFromFile("images/right.png")) {
    std::cerr << "Failed to load texture, error: " << std::endl;
    success = false;
  }

  return success;
}

void close()
{
  arrow->DeallocateTexture();

  SDL_JoystickClose(game_controller);
  game_controller = nullptr;

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson19()
{
  if (!init()) {
    std::cerr << "Failed to initialize\n";
  } else {
    if (!loadMedia()) {
      std::cerr << "Failed to load media\n";
    } else {
      bool quit = false;
      SDL_Event e;

      // Normalized direction
      int x_dir = 0;
      int y_dir = 0;

      Texture* current_texture = arrow.get();

      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_JOYAXISMOTION) {
            // If the input was from the controller 0
            if (e.jaxis.which == 0) {
              // X axis motion
              if (e.jaxis.axis == 0) {
                if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                  x_dir = -1;
                } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                  x_dir = 1;
                } else {
                  x_dir = 0;
                }
              } else if (e.jaxis.axis == 1) {
                // Y axis motion
                if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                  y_dir = -1;
                } else if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                  y_dir = 1;
                } else {
                  y_dir = 0;
                }
              }
            }
          }
          // Clear screen
          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
          SDL_RenderClear(renderer);

          // Calculate the angle
          double joystick_angle = atan2((double)y_dir, double(x_dir)) * (180.0 / M_PI);

          if (x_dir == 0 && y_dir == 0) {
            joystick_angle = 0;
          }

          current_texture->Render(0, 0, nullptr, joystick_angle);
          // Update screen
          SDL_RenderPresent(renderer);
        }
        // SDL_Delay(1000);
      }
      close();
    }
  }
}
} // namespace lesson19
} // namespace sdl_lazyfoo