#include "chapter2.hpp"

#if _WIN32 || _WIN64
#include <windows.h>
#endif

// Order of SDL and gl headers is important
#include <SDL2/SDL.h>
#include <gl/glew.h>

#include <SDL2/SDL_opengl.h>
#include <gl/glu.h>

#include <cstdio>
#include <memory>
#include <string>

namespace chapter2
{
namespace
{
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL, creates window and initializes OpenGL
bool init();
// Initialized matrices and clear color
bool initGL();
// Input handler
void handleKeys(unsigned char key, int x, int y);
// Per frame update
void update();
// Renders quad to the screen
void render();
// Frees media and shuts down SDL
void close();

SDL_Window* window = nullptr;
// OpenGL context
SDL_GLContext context;
bool renderQuad = true;

bool init()
{
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! Error: %s\n", SDL_GetError());
    success = false;
  } else {
    // Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Create window
    window = SDL_CreateWindow("Chapter 2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                              SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == nullptr) {
      printf("Window could not be created. Error: %s\n", SDL_GetError());
      success = false;
    } else {
      context = SDL_GL_CreateContext(window);
      if (context == nullptr) {
        printf("OpenGL context could not be created! Error: %s\n", SDL_GetError());
        success = false;
      } else {
        // Use VSync
        if (SDL_GL_SetSwapInterval(1) < 0) {
          printf("Warning: Unable to set VSync for OpenGL. Error: %s\n", SDL_GetError());
        }

        // Initalize OpenGL
        if (!initGL()) {
          printf("Unable to initialize OpenGL\n");
          success = false;
        }
      }
    }
  }
  return success;
}

bool initGL()
{
  bool success = true;

  GLenum error = GL_NO_ERROR;

  // Initialize projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Check for error
  error = glGetError();
  if (error != GL_NO_ERROR) {
    printf("Error initalizing OpenGL! %s\n", gluErrorString(error));
    success = false;
  }

  // Initialize clear color
  glClearColor(0.f, 0.f, 0.f, 1.f);

  error = glGetError();
  if (error != GL_NO_ERROR) {
    printf("Error initalizing OpenGL! %s\n", gluErrorString(error));
    success = false;
  }

  return success;
}

void handleKeys(unsigned char key, int x, int y)
{
  // Toggle quad
  if (key == 'q') {
    renderQuad = !renderQuad;
  }
}

void update()
{
  // No per frame update needed
}

void render()
{
  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT);

  // Render quad
  if (renderQuad) {
    glBegin(GL_QUADS);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(-0.5f, 0.5f);
    glEnd();
  }
}

void close()
{
  SDL_DestroyWindow(window);
  SDL_Quit();
}

} // namespace

void chapter2()
{
  if (!init()) {
    printf("Failed to initialize\n");
  } else {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    SDL_StartTextInput();
    while (!quit) {
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
          quit = true;
        } else if (e.type == SDL_TEXTINPUT) {
          int x = 0, y = 0;
          SDL_GetMouseState(&x, &y);
          handleKeys(e.text.text[0], x, y);
        }
      }

      render();
      SDL_GL_SwapWindow(window);
    }
    SDL_StopTextInput();
  }

  close();
}
} // namespace chapter2