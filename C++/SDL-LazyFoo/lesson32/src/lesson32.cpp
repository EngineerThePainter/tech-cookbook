#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#include "lesson32/dot.hpp"
#include "lesson32/lesson32.hpp"
#include "lesson32/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson32
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

    window = SDL_CreateWindow("SDL Tutorial Lazy Foo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              Dot::SCREEN_WIDTH, Dot::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      std::cerr << "Windows could not be initialized: " << SDL_GetError() << std::endl;
      success = false;
    } else {
      // Disabled V-Sync to do it manually
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
    std::cerr << "Failed to load texturr, error: " << SDL_GetError() << std::endl;
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

void lesson32()
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

      SDL_Color text_color = {0,0,0,0xFF};

      std::string inputText = "Some text";
      texture->LoadFromRenderedText(inputText.c_str(), text_color);

      SDL_StartTextInput();

      while (!quit) {
        bool renderText = false;
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            // Handle backspace
            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0) {
              inputText.pop_back();
              renderText = true;
            }// Handle copy 
            else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
              SDL_SetClipboardText(inputText.c_str());
            }// Handle paste
            else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
              inputText = SDL_GetClipboardText();
              renderText = true;
            } 
          }  // Special text input event
          else if (e.type == SDL_TEXTINPUT) {
              // Not copy or pasting
              if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) ) {
                  inputText += e.text.text;
                  renderText = true;
              }
            }
        }

        if (renderText) {
          if (inputText != "") {
            texture->LoadFromRenderedText(inputText.c_str(), text_color);
          } else {
            texture->LoadFromRenderedText(" ", text_color);
          }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

        texture->Render( ( SCREEN_WIDTH - texture->GetWidth() ) / 2, texture->GetHeight() );

        SDL_RenderPresent(renderer);
      }

      SDL_StopTextInput();
      close();
    }
  }
}
} // namespace lesson32
} // namespace sdl_lazyfoo