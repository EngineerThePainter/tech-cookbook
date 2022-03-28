#include <iostream>
#include <memory>
#include <string>

#include "lesson20/lesson20.hpp"
#include "lesson20/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL_gamecontroller.h>
#include <SDL_haptic.h>
#include <SDL_image.h>
#include <SDL_joystick.h>

namespace sdl_lazyfoo
{
namespace lesson20
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int JOYSTICK_DEAD_ZONE = 8000;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_GameController* game_controller = nullptr;
SDL_Joystick* joystick = nullptr;
SDL_Haptic* joy_haptic = nullptr;

std::unique_ptr<Texture> arrow;
} // namespace

bool init()
{
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER) < 0) {
    std::cerr << "SDL could not initialize SDL Error: " << SDL_GetError() << std::endl;
    success = false;
  } else {

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      std::cerr << "Warning: Linear texture filtering not enabled!";
    }

    if (SDL_NumJoysticks() < 1) {
      std::cerr << "No joysticks connected!";
    } else {
      if (SDL_IsGameController(0)) {
        std::cerr << "Error: joystick is not game controller interface compatible. Error: " << SDL_GetError()
                  << std::endl;
      } else {
        game_controller = SDL_GameControllerOpen(0);
        if (!SDL_GameControllerHasRumble(0)) {
          std::cerr << "Warning: game controller does not support rumble. Error: " << SDL_GetError() << std::endl;
        }
      }

      // Load joystick if game controller cannot be initialized
      if (game_controller == nullptr) {
        joystick = SDL_JoystickOpen(0);
        if (joystick == nullptr) {
          std::cerr << "Could not open the game controller. Error: " << SDL_GetError() << std::endl;
        } else {
          if (!SDL_JoystickIsHaptic(joystick)) {
            std::cerr << "Warning: joystick does not support haptic. Error: " << SDL_GetError() << std::endl;
          } else {
            joy_haptic = SDL_HapticOpenFromJoystick(joystick);
            if (joy_haptic == nullptr) {
              std::cerr << "Warning: unable to get joystick haptic. Error: " << SDL_GetError() << std::endl;
            } else {
              if (SDL_HapticRumbleInit(joy_haptic) < 0) {
                std::cerr << "Warning: unable to open haptic rumble. Error: " << SDL_GetError() << std::endl;
              }
            }
          }
        }
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

  if (game_controller != nullptr) {
    SDL_GameControllerClose(game_controller);
  }

  if (joy_haptic != nullptr) {
    SDL_HapticClose(joy_haptic);
  }

  if (joystick != nullptr) {
    SDL_JoystickClose(joystick);
  }

  game_controller = nullptr;
  joy_haptic = nullptr;
  joystick = nullptr;

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  IMG_Quit();
  SDL_Quit();
}

void lesson20()
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
          } else if (e.type == SDL_JOYBUTTONDOWN) {
            if (game_controller) {
              if (SDL_GameControllerRumble(game_controller, 0xFFFF * 3 / 4, 0xFFFF * 3 / 4, 500) != 0) {
                std::cerr << "Unable to play controller rumble: " << SDL_GetError() << std::endl;
              }
            } else if (joy_haptic) {
              if (SDL_HapticRumblePlay(joy_haptic, 0.75, 500) != 0) {
                std::cerr << "Unable to play haptic rumble: " << SDL_GetError() << std::endl;
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
} // namespace lesson20
} // namespace sdl_lazyfoo