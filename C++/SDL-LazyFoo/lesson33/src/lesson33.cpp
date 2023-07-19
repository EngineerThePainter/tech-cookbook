#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "lesson33/dot.hpp"
#include "lesson33/lesson33.hpp"
#include "lesson33/texture.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace sdl_lazyfoo
{
namespace lesson33
{
namespace
{

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int TOTAL_DATA = 10;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

std::vector<Texture> dataTextures;
Sint32 data[TOTAL_DATA];

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
      }
    }
  }

  for (int i = 0; i < TOTAL_DATA; ++i) {
    dataTextures.push_back(Texture(renderer));
  }

  return success;
}

bool loadMedia()
{
  SDL_Color textColor = { 0, 0, 0, 0xFF };
	SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

  bool success = true;

  for (int i = 0; i < TOTAL_DATA; ++i) {
    dataTextures[i].LoadTextFromfile("images/lazy.ttf");
  }

  SDL_RWops* file = SDL_RWFromFile("images/nums.bin", "r+b");
  if (file == nullptr) {
    std::cerr << "Unable to open file: " << SDL_GetError() << std::endl;\
    file = SDL_RWFromFile("images/nums.bin", "w+b");
    if (file != nullptr) {
      std::cerr << "New file created\n";
      for (int i = 0; i < TOTAL_DATA; ++i) {
        data[i] = 0;
        SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
      }
      SDL_RWclose(file);
    } else {
      std::cerr << "Unable to create file. Error: " << SDL_GetError() << std::endl;
      success = false;
    }
  } else {
    std::cerr << "Reading file\n";
    for (int i = 0; i < TOTAL_DATA; ++i) {
      SDL_RWread(file, &data[i], sizeof(Sint32), 1);
    } 
    SDL_RWclose(file);
  }

  dataTextures[0].LoadFromRenderedText(std::to_string(data[0]), highlightColor);
  for (int i = 1; i < TOTAL_DATA; ++i) {
    dataTextures[i].LoadFromRenderedText(std::to_string(data[i]), textColor);
  }

  return success;
}

void close()
{

  SDL_RWops* file = SDL_RWFromFile("images/nums.bin", "w+b");
  if (file != nullptr) {
    for (int i = 0; i < TOTAL_DATA; ++i) {
      SDL_RWwrite(file, &data[i], sizeof(Sint32), 1);
    }
    SDL_RWclose(file);
  } else {
    std::cerr << "Unable to save file. Error " << SDL_GetError() << std::endl;
  }

  SDL_DestroyRenderer(renderer);
  renderer = nullptr;

  SDL_DestroyWindow(window);
  window = nullptr;

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void lesson33()
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

      SDL_Color textColor = { 0, 0, 0, 0xFF };
      SDL_Color highlightColor = { 0xFF, 0, 0, 0xFF };

      int currentData = 0;

      while (!quit) {

        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym)
            {
              //Previous data entry
              case SDLK_UP:
              //Rerender previous entry input point
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), textColor );
              --currentData;
              if( currentData < 0 )
              {
                  currentData = TOTAL_DATA - 1;
              }
              
              //Rerender current entry input point
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), highlightColor );
              break;
              
              //Next data entry
              case SDLK_DOWN:
              //Rerender previous entry input point
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), textColor );
              ++currentData;
              if( currentData == TOTAL_DATA )
              {
                  currentData = 0;
              }
              
              //Rerender current entry input point
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), highlightColor );
              break;
                                          //Decrement input point
              case SDLK_LEFT:
              --data[ currentData ];
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), highlightColor );
              break;
              
              //Increment input point
              case SDLK_RIGHT:
              ++data[ currentData ];
              dataTextures[ currentData ].LoadFromRenderedText( std::to_string( data[ currentData ] ), highlightColor );
              break;
            }
          }
        }

        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);

      for (int i = 0; i < TOTAL_DATA; ++i) {
        dataTextures[ i ].Render( ( SCREEN_WIDTH - dataTextures[ i ].GetWidth() ) / 2, 50 + dataTextures[ 0 ].GetHeight() * i );
      }

        SDL_RenderPresent(renderer);
      }

      close();
    }
  }
}
} // namespace lesson33
} // namespace sdl_lazyfoo