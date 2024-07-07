#include "../include/ProgramController.h"
#include "../include/Raycaster.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

ProgramController::ProgramController ()
    : _state (ProgramState::RUN), _window_title ("PROGRAM WINDOW"),
      _window (nullptr), _renderer (nullptr), _window_width (640),
      _window_height (480), _raycaster (_window_width, _window_height)
{
  this->init_systems ();
  this->main_loop ();
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

  _renderer = SDL_CreateRenderer (
      _window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

  if (_renderer == nullptr)
    {
      fatal_error ("Failed to create renderer with SDL2");
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
ProgramController::draw ()
{
  if (_renderer == nullptr)
    {
      fatal_error ("Renderer is nullptr in draw method");
    }
  _raycaster.render_frame (_renderer);
}

void
ProgramController::fatal_error (std::string error)
{
  std::cout << error << '\n';
  if (SDL_GetError ())
    {
      std::cout << "Last SDL2 error: " << SDL_GetError () << '\n';
    }
  std::cout << "Fatal error, enter any string to close the application" << '\n';
  char input;
  std::cin >> input;
  SDL_Quit ();
  exit (EXIT_FAILURE);
}

void
ProgramController::main_loop ()
{
  // Keep window open until closed
  while (_state == ProgramState::RUN)
    {
      // Poll for events and update on event
      process_input ();
      // Update window
      draw ();
    }
}
