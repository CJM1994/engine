#include "../include/ProgramController.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

ProgramController::ProgramController ()
    : _state (ProgramState::RUN), _window_title ("DOOM"), _window (nullptr),
      _window_width (640), _window_height (400)
{
}

void
ProgramController::init_systems ()
{
  // SDL
  if (SDL_Init (SDL_INIT_VIDEO) < 0)
    {
      fatal_error ("Failed to initialize the SDL2 library");
    }
  _window = SDL_CreateWindow (_window_title, SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, _window_width,
                              _window_height, 0);
  if (_window == nullptr)
    {
      fatal_error ("Failed to create window with SDL2");
    }
  // OpenGL
  SDL_GLContext const gl_context{ SDL_GL_CreateContext (_window) };
  if (gl_context == nullptr)
    {
      fatal_error ("Failed to create SDL_GLContext");
    }
};

void
ProgramController::process_input ()
{
  SDL_Event e;
  while (SDL_PollEvent (&e) > 0)
    {
      switch (e.type)
        {
        case SDL_QUIT:
          _state = ProgramState::HALT;
        case SDL_KEYDOWN:
          std::cout << "key pressed: " << e.key.keysym.scancode << '\n';
          break;
        }
    }
}

void
ProgramController::fatal_error (std::string error)
{
  std::cout << error << '\n';
  if (SDL_GetError ())
    {
      std::cout << "Last SDL2 error: " << SDL_GetError () << '\n';
    }
  std::cout << "Fatal error, enter any string to close the application"
            << '\n';
  char input;
  std::cin >> input;
  SDL_Quit ();
  exit (EXIT_FAILURE);
}

void
ProgramController::main_loop ()
{
  // NOTE: Placeholder graphic for window surface
  SDL_Surface *window_surface = SDL_GetWindowSurface (_window);
  if (!window_surface)
    {
      fatal_error ("Failed to create surface with SDL2");
    }
  SDL_Surface *image = SDL_LoadBMP ("assets/doom.bmp");
  if (!image)
    {
      fatal_error ("Failed to load image with SDL2");
    }

  // Keep window open until closed
  while (_state == ProgramState::RUN)
    {
      // Poll for events and update on event
      process_input ();
      // Update window
      SDL_BlitSurface (image, NULL, window_surface, NULL);
      SDL_UpdateWindowSurface (_window);
    }
}

void
ProgramController::run ()
{
  ProgramController::init_systems ();
  ProgramController::main_loop ();
};
